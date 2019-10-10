
#include <QDebug>

#include "wcm/wcm-database.h"
#include "wcm/wcm-column.h"
#include "wcm/wcm-column-set.h"

//#include "patient.h"

//#include "whitedb.h"

#include <QCoreApplication>

#include "wcm/wcm-hypernode.h"
#include "wcm/wcm-hyponode.h"

#include "ntxh-parser/ntxh-document.h"

#include "kans.h"

#include "clo-species.h"

int main2(int argc, char *argv[])
{
 WCM_Database qwdb("200", DEFAULT_WCM_FOLDER "/test/test-200.wdb");

 qwdb.re_create();

 qwdb.create_new_column("@Species");
 qwdb.create_new_column("Default@Species");
 qwdb.create_new_column("Species::Abbreviation");

 // WCM_Column* name_column = qwdb.create_new_column("Patient::Name");


// WCM_Column* patient_type_column = qwdb.create_new_column("@Patient");
// WCM_Column* patient_default_column = qwdb.create_new_column("Default@Patient");

// WCM_Column* name_column = qwdb.create_new_column("Patient::Name");
// WCM_Column* patient_id_column = qwdb.create_new_column("Patient::Id");

 qwdb.save();

 return 0;
}

int main(int argc, char *argv[])
{
// WCM_Database qwdb("100", DEFAULT_WCM_FOLDER "/test/test-100.wdb");

 NTXH_Document doc(DEFAULT_WCM_FOLDER "/species.ntxh");

 doc.parse();

 typedef NTXH_Graph::hypernode_type hypernode_type;

//? NTXH_Graph& g = *doc.graph();

 QVector<CLO_Species*> species;

 QVector<NTXH_Graph::hypernode_type*>& hns = doc.top_level_hypernodes();

 for(NTXH_Graph::hypernode_type* hn : hns)
 {
  doc.graph()->get_sfsr(hn, {{1,3}}, [&species]
    (QVector<QPair<QString, void*>>& prs)
  {
   CLO_Species* s = new CLO_Species;
   s->set_abbreviation(prs[0].first);
   s->set_instances(prs[1].first);
   s->set_name(prs[2].first);
   species.push_back(s);
  });
 }

 WCM_Database qwdb("200", DEFAULT_WCM_FOLDER "/test/test-200.wdb");

 for(CLO_Species* s : species)
 {
  WCM_Hypernode whn;
//  WCM_Hyponode** whos = qwdb.new_hyponode_array(3) << [s]
//    (WCM_WhiteDB& wdb, WCM_Hyponode* who, quint32 index)
//  {
//   switch (index)
//   {
//   case 0:
//    who->set_wgdb_encoding({wdb.encode_string(s->abbreviation())});
//    break;
//   case 1:
//    who->set_qt_encoding(s->instances().toUInt());
//    break;
//   case 2:
//    who->set_qt_encoding(s->name());
//    break;
//   }
//  };
//  whn.add_hyponodes(whos)(3);
  WCM_Hyponode** whos = qwdb.new_hyponode_array(3);
  whos[0]->set_wgdb_encoding({qwdb.wdb().encode_string(s->abbreviation())});
  whos[1]->set_qt_encoding(s->instances().toUInt());
  whos[2]->set_qt_encoding(s->name());

  whn.add_hyponodes(whos)(3);

  whn.add_to_database(qwdb, "@Species", "Default@Species");

  qwdb.save();

 }




// qwdb.load();
 return  0;

}

int main3(int argc, char *argv[])
{
 WCM_Database qwdb("200", DEFAULT_WCM_FOLDER "/test/test-200.wdb");
 qwdb.load();

 WCM_Hypernode whn;

 QByteArray qba;

 qwdb.retrieve_record(qba, "Default@Species", "Species::Abbreviation",
   QString("BTBW"));

 WCM_Column_Set qwcs(qwdb);

 QMap<quint32, QString> icm;
 icm[0] = "Species::Abbreviation";

 whn.set_indexed_column_map(&icm);
 whn.absorb_data(qba, qwcs);

 whn.with_hyponode(0) << [&qwdb](WCM_Hyponode& who)
 {
  wg_int wgi = who.wgdb_encoding().data;
  QString abbr = qwdb.wdb().decode_string(wgi);
  qDebug() << abbr;
 };

 whn.with_hyponode(1) << [](WCM_Hyponode& who)
 {
  QVariant qv = who.qt_encoding();
  quint32 num = qv.toInt();
  qDebug() << num;
 };

 whn.with_hyponode(2) << [](WCM_Hyponode& who)
 {
  QVariant qv = who.qt_encoding();
  QString qs = qv.toString();
  qDebug() << qs;
 };

 return 0;
}



int main4(int argc, char *argv[])
{
 WCM_Database qwdb("100", DEFAULT_WCM_FOLDER "/test/test-100.wdb");

 NTXH_Document doc(DEFAULT_WCM_FOLDER "/species.ntxh");

 doc.parse();

 qwdb.load();

 WCM_Hypernode whn;

 QByteArray qba;

 qwdb.retrieve_record(qba, "Default@Patient", "Patient::Id", 1000);

 WCM_Column_Set qwcs(qwdb);

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

 whn.with_hyponode(2) << [&qwdb](WCM_Hyponode& who)
 {
  wg_int wgi = who.wgdb_encoding().data;
  quint32 pi = qwdb.wdb().decode_u4(wgi);
  qDebug() << pi;
 };

// quint32 record_index;

// qwdb.add_record("@Patient", "Default@Patient", qba, record_index);

 return 0;
}

int main1(int argc, char *argv[])
{
 WCM_Database qwdb("100", DEFAULT_WCM_FOLDER "/test/test-100.wdb");
 qRegisterMetaType<WCM_Encoding_Package>();

 qwdb.load();
 
 WCM_Hypernode whn;

 WCM_Hyponode* who1 = new WCM_Hyponode;
 WCM_Hyponode* who2 = new WCM_Hyponode;
 WCM_Hyponode* who3 = new WCM_Hyponode;

 QVariant v1(QString("Test Name"));
 QVariant v2(QDate::fromString("June 4, 2005", "MMMM d, yyyy"));
 wg_int v3 = qwdb.wdb().encode_u4(1000);
 
 who1->set_qt_encoding(v1);
 who2->set_qt_encoding(v2);
 who3->set_wgdb_encoding({v3});

 whn.add_hyponodes({who1, who2, who3});

 QMap<quint32, QString> icm;
 icm[2] = "Patient::Id";

 whn.set_indexed_column_map(&icm);

 WCM_Column_Set qwcs(qwdb);

 QByteArray qba;

 whn.supply_data(qba, qwcs);

 quint32 record_index;

 qwdb.add_record("@Patient", "Default@Patient", qba, record_index);
 qwdb.save();
 return 0;
}
