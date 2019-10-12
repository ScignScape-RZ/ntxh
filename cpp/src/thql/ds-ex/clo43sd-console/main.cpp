
#include <QDebug>

#include "wcm/wcm-database.h"
#include "wcm/wcm-column.h"
#include "wcm/wcm-column-set.h"

//#include "patient.h"

//#include "whitedb.h"

#include <QCoreApplication>

#include "wcm/wcm-hypernode.h"
#include "wcm/wcm-hyponode.h"
#include "withs.h"

#include "ntxh-parser/ntxh-document.h"

#include "kans.h"

#include "clo-species.h"

int main3(int argc, char *argv[])
{
 WCM_Database wcmd("200", DEFAULT_WCM_FOLDER "/test/test-200.wdb");

 wcmd.re_create();

 wcmd.create_new_column("@Species");
 wcmd.create_new_column("Default@Species");
 wcmd.create_new_column("Species::Abbreviation");

 wcmd.create_new_column("@Info");
 wcmd.create_new_singleton_column("Default@Info");
// wcmd.create_new_column("Species::Abbreviation");

 // WCM_Column* name_column = wcmd.create_new_column("Patient::Name");


// WCM_Column* patient_type_column = wcmd.create_new_column("@Patient");
// WCM_Column* patient_default_column = wcmd.create_new_column("Default@Patient");

// WCM_Column* name_column = wcmd.create_new_column("Patient::Name");
// WCM_Column* patient_id_column = wcmd.create_new_column("Patient::Id");

 wcmd.save();

 return 0;
}

int main2(int argc, char *argv[])
{
// WCM_Database wcmd("100", DEFAULT_WCM_FOLDER "/test/test-100.wdb");

 NTXH_Document doc(DEFAULT_WCM_FOLDER "/species.ntxh");

 doc.parse();

 typedef NTXH_Graph::hypernode_type hypernode_type;

//? NTXH_Graph& g = *doc.graph();

 QVector<CLO_Species*> species;

 QVector<NTXH_Graph::hypernode_type*>& hns = doc.top_level_hypernodes();

 QMap<quint32, QString> icm;
 icm[0] = "Species::Abbreviation";

 for(NTXH_Graph::hypernode_type* hn : hns)
 {
  doc.graph()->get_sfsr(hn, {{1,3}}, [&species]
    (QVector<QPair<QString, void*>>& prs)
  {
   CLO_Species* s = new CLO_Species;
   s->set_abbreviation(prs[0].first);
   s->set_instances(prs[1].first.toUInt());
   s->set_name(prs[2].first);
   species.push_back(s);
  });
 }

 WCM_Database wcmd("200", DEFAULT_WCM_FOLDER "/test/test-200.wdb");
 qRegisterMetaType<WCM_Encoding_Package>();
 wcmd.load();

 // // init info hypernode
 {
  WCM_Hypernode whn;

  wcmd.with_new_hyponode_array(2) << [&wcmd, &whn, &hns](WCM_Hyponode** whos)
  {
   whos[0]->set_qt_encoding(hns.size());
   whos[1]->set_qt_encoding("/home/nlevisrael/hypergr/bird/CLO-43SD"_q_());
   whn.add_hyponodes(whos)[2];
   whn.add_to_database(wcmd, "@Info", "Default@Info");
  };
 }

 for(CLO_Species* s : species)
 {
  WCM_Hypernode whn;
  wcmd.with_new_hyponode_array(3) << [&wcmd, &whn, &icm, s](WCM_Hyponode** whos)
  {
   whos[0]->set_wgdb_encoding({wcmd.wdb().encode_string(s->abbreviation())});
   whos[1]->set_qt_encoding(s->instances());
   whos[2]->set_qt_encoding(s->name());
   whn.add_hyponodes(whos)[3];
   whn.set_indexed_column_map(&icm);
   whn.add_to_database(wcmd, "@Species", "Default@Species");
  };
  wcmd.save();
 }




// wcmd.load();
 return  0;

}

int main(int argc, char *argv[])
{
 WCM_Database wcmd("200", DEFAULT_WCM_FOLDER "/test/test-200.wdb");
 wcmd.load();

 WCM_Column_Set qwcs(wcmd);

// wcmd.create_new_column("@CLO_File");
// wcmd.create_new_column("Default@CLO_File");
// wcmd.create_new_column("Species::Abbreviation@CLO_File");
// wcmd.save();
 u4 species_count;
 QString ds_root;

 // //  retrieve info
 {
  WCM_Hypernode whn;
  QByteArray qba;
  wcmd.retrieve_record(qba, "Default@Info");
  whn.absorb_data(qba, qwcs);
  whn.with_hyponode(0) << [&species_count](WCM_Hyponode& who)
  {
   species_count = who.qt_encoding().toInt();
  };
  whn.with_hyponode(1) << [&ds_root](WCM_Hyponode& who)
  {
   ds_root = who.qt_encoding().toString();
  };

  qDebug() << species_count;
  qDebug() << ds_root;
 }

 QDir qd("/home/nlevisrael/hypergr/bird/CLO-43SD");
// QFileInfoList qsl = qd.entryInfoList(QDir::Files | QDir::NoDotAndDotDot);

 with_files(QDir(ds_root)).filter({"*.py"}) << [](QFileInfo& qfi)
 {
  qDebug() << qfi.absoluteFilePath();
 };
}

int main5(int argc, char *argv[])
{
 WCM_Database wcmd("200", DEFAULT_WCM_FOLDER "/test/test-200.wdb");
 wcmd.load();

 WCM_Column_Set qwcs(wcmd);

 u4 species_count;
 QString ds_root;

 // //  retrieve info
 {
  WCM_Hypernode whn;
  QByteArray qba;
  wcmd.retrieve_record(qba, "Default@Info");
  whn.absorb_data(qba, qwcs);
  whn.with_hyponode(0) << [&species_count](WCM_Hyponode& who)
  {
   species_count = who.qt_encoding().toInt();
  };
  whn.with_hyponode(1) << [&ds_root](WCM_Hyponode& who)
  {
   ds_root = who.qt_encoding().toString();
  };

  qDebug() << species_count;
  qDebug() << ds_root;
 }

 QMap<quint32, QString> icm;
 icm[0] = "Species::Abbreviation";

 QVector<CLO_Species*> species_vec;
 QMap<QString, CLO_Species*> species_map;

 u4 sc = wcmd.get_record_count("Default@Species");
 species_vec.resize(sc);

 // // retrieve species ...
 wcmd.with_all_column_records("Default@Species") <<
   [&icm, &qwcs, &wcmd, &species_vec, &species_map]
   (QByteArray& qba, u4 i)
 {
  WCM_Hypernode whn;
  whn.set_indexed_column_map(&icm);
  whn.absorb_data(qba, qwcs);

  CLO_Species* sp = new CLO_Species;
  species_vec[i] = sp;

  whn.with_hyponode(0) << [&wcmd, sp, &species_map](WCM_Hyponode& who)
  {
   wg_int wgi = who.wgdb_encoding().data;
   QString abbr = wcmd.wdb().decode_string(wgi);
//   qDebug() << abbr;
   sp->set_abbreviation(abbr);
   species_map[abbr] = sp;
  };

  whn.with_hyponode(1) << [sp](WCM_Hyponode& who)
  {
   QVariant qv = who.qt_encoding();
   u4 num = qv.toUInt();
 //  qDebug() << num;
   sp->set_instances(num);
  };

  whn.with_hyponode(2) << [sp](WCM_Hyponode& who)
  {
   QVariant qv = who.qt_encoding();
   QString qs = qv.toString();
   sp->set_name(qs);
//   qDebug() << qs;
  };
 };

// for(CLO_Species* sp : species_vec)
// {
//  QString logmelspec = ds_root + "/logmelspec";
// }

 with_map(species_map) << [](QString abbreviation, CLO_Species* clo)
 {
  qDebug() << abbreviation;

 };


// for(quint32 i = 1; i <= species_count; ++i)
// {
//  WCM_Hypernode whn;
//  QByteArray qba;
//  wcmd.retrieve_indexed_record(qba, "Default@Species", i);
//  whn.set_indexed_column_map(&icm);
//  whn.absorb_data(qba, qwcs);

//  whn.with_hyponode(0) << [&wcmd](WCM_Hyponode& who)
//  {
//   wg_int wgi = who.wgdb_encoding().data;
//   QString abbr = wcmd.wdb().decode_string(wgi);
//   qDebug() << abbr;
//  };

//  whn.with_hyponode(1) << [](WCM_Hyponode& who)
//  {
//   QVariant qv = who.qt_encoding();
//   quint32 num = qv.toInt();
//   qDebug() << num;
//  };

//  whn.with_hyponode(2) << [](WCM_Hyponode& who)
//  {
//   QVariant qv = who.qt_encoding();
//   QString qs = qv.toString();
//   qDebug() << qs;
//  };

// }

// WCM_Hypernode whn;

// QByteArray qba;

// wcmd.retrieve_record(qba, "Default@Species", "Species::Abbreviation",
//   "BTBW"_q_());

// whn.set_indexed_column_map(&icm);
// whn.absorb_data(qba, qwcs);

// whn.with_hyponode(0) << [&wcmd](WCM_Hyponode& who)
// {
//  wg_int wgi = who.wgdb_encoding().data;
//  QString abbr = wcmd.wdb().decode_string(wgi);
//  qDebug() << abbr;
// };

// whn.with_hyponode(1) << [](WCM_Hyponode& who)
// {
//  QVariant qv = who.qt_encoding();
//  quint32 num = qv.toInt();
//  qDebug() << num;
// };

// whn.with_hyponode(2) << [](WCM_Hyponode& who)
// {
//  QVariant qv = who.qt_encoding();
//  QString qs = qv.toString();
//  qDebug() << qs;
// };

 return 0;
}



int main4(int argc, char *argv[])
{
 WCM_Database wcmd("100", DEFAULT_WCM_FOLDER "/test/test-100.wdb");

 NTXH_Document doc(DEFAULT_WCM_FOLDER "/species.ntxh");

 doc.parse();

 wcmd.load();

 WCM_Hypernode whn;

 QByteArray qba;

 wcmd.retrieve_record(qba, "Default@Patient", "Patient::Id", 1000);

 WCM_Column_Set qwcs(wcmd);

 QMap<quint32, QString> icm;
 icm[2] = "Patient::Id";

 whn.set_indexed_column_map(&icm);
 whn.absorb_data(qba, qwcs);

 whn.with_hyponode(0) << [](WCM_Hyponode& who)
 {
  QVariant qv = who.qt_encoding();
  QString qs = qv.toString();
  qDebug() << qs;
 };

 whn.with_hyponode(1) << [](WCM_Hyponode& who)
 {
  QVariant qv = who.qt_encoding();
  QDate qd = qv.toDate();
  qDebug() << qd.toString();
 };

 whn.with_hyponode(2) << [&wcmd](WCM_Hyponode& who)
 {
  wg_int wgi = who.wgdb_encoding().data;
  quint32 pi = wcmd.wdb().decode_u4(wgi);
  qDebug() << pi;
 };

// quint32 record_index;

// wcmd.add_record("@Patient", "Default@Patient", qba, record_index);

 return 0;
}

int main1(int argc, char *argv[])
{
 WCM_Database wcmd("100", DEFAULT_WCM_FOLDER "/test/test-100.wdb");
 qRegisterMetaType<WCM_Encoding_Package>();

 wcmd.load();
 
 WCM_Hypernode whn;

 WCM_Hyponode* who1 = new WCM_Hyponode;
 WCM_Hyponode* who2 = new WCM_Hyponode;
 WCM_Hyponode* who3 = new WCM_Hyponode;

 QVariant v1(QString("Test Name"));
 QVariant v2(QDate::fromString("June 4, 2005", "MMMM d, yyyy"));
 wg_int v3 = wcmd.wdb().encode_u4(1000);
 
 who1->set_qt_encoding(v1);
 who2->set_qt_encoding(v2);
 who3->set_wgdb_encoding({v3});

 whn.add_hyponodes({who1, who2, who3});

 QMap<quint32, QString> icm;
 icm[2] = "Patient::Id";

 whn.set_indexed_column_map(&icm);

 WCM_Column_Set qwcs(wcmd);

 QByteArray qba;

 whn.supply_data(qba, qwcs);

 quint32 record_index;

 wcmd.add_record("@Patient", "Default@Patient", qba, record_index);
 wcmd.save();
 return 0;
}


//WCM_Hyponode* whos[2];
//whos[0] = new WCM_Hyponode;
//whos[0]->set_qt_encoding(hns.size());
//whos[1] = new WCM_Hyponode;
//whos[1]->set_qt_encoding("/home/nlevisrael/hypergr/bird/CLO-43SD"_q_());
//whn.add_hyponodes(whos, 2);
//whn.add_to_database(wcmd, "@Info", "Default@Info");


// //  WCM_Hyponode** whos = wcmd.new_hyponode_array(2);
// //  whos[0]->set_qt_encoding(hns.size());
// //  whos[1]->set_qt_encoding("/home/nlevisrael/hypergr/bird/CLO-43SD"_q_());
// //  whn.add_hyponodes(whos)(2);
// //  whn.add_to_database(wcmd, "@Info", "Default@Info");

// //  WCM_Hyponode** whos = wcmd.new_hyponode_array(3) << [s]
// //    (WCM_WhiteDB& wdb, WCM_Hyponode* who, quint32 index)
// //  {
// //   switch (index)
// //   {
// //   case 0:
// //    who->set_wgdb_encoding({wdb.encode_string(s->abbreviation())});
// //    break;
// //   case 1:
// //    who->set_qt_encoding(s->instances().toUInt());
// //    break;
// //   case 2:
// //    who->set_qt_encoding(s->name());
// //    break;
// //   }
// //  };
// //  whn.add_hyponodes(whos)(3);
//  WCM_Hyponode** whos = wcmd.new_hyponode_array(3);

//  whos[0]->set_wgdb_encoding({wcmd.wdb().encode_string(s->abbreviation())});
//  whos[1]->set_qt_encoding(s->instances().toUInt());
//  whos[2]->set_qt_encoding(s->name());

//  whn.add_hyponodes(whos)(3);
