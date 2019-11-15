
#include <QDebug>

#include "wcm/wcm-database.h"
#include "wcm/wcm-column.h"
#include "wcm/wcm-column-set.h"

#include <QMediaPlayer>
#include <QApplication>
#include <QClipboard>

#include <QSound>

//#include "patient.h"

//#include "whitedb.h"

#include <QCoreApplication>

#include "wcm/wcm-hypernode.h"
#include "wcm/wcm-hyponode.h"
#include "withs.h"

#include "clo-file.h"
#include "clo43sd-data/clo-database.h"
#include "clo43sd-data/clo-species.h"

#include "ntxh-parser/ntxh-document.h"

#include "QScign/ScignStage/ScignStage-audio/scignstage-audio-dialog.h"
#include "QScign/ScignStage/ScignStage-audio/scignstage-audio-tablemodel.h"


#include "kans.h"

#include "clo43sd-data/clo-species-display-info.h"


void load_species(WCM_Database& wcmd,
  WCM_Column_Set& wcs, CLO_Database& cdb)
{
 QVector<CLO_Species*>& species_vec = cdb.species_vec();
 QMap<QString, CLO_Species*>& species_map = cdb.species_map();

 QMap<u4, QString> icm;
 icm[0] = "Species::Abbreviation";

 QMap<CLO_Species*, CLO_File*> species_files;

 u4 sc = wcmd.get_record_count("Default@Species");
 species_vec.resize(sc);

 // // retrieve species ...
 wcmd.with_all_column_records("Default@Species") <<
   [&icm, &wcs, &wcmd, &species_vec, &species_map]
   (QByteArray& qba, u4 i)
 {
  WCM_Hypernode whn;
  whn.set_indexed_column_map(&icm);
  whn.absorb_data(qba, wcs);

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
}

QPair<QMediaPlayer*, QPair<quint8, quint8>*> get_media_player()
{
 static QMediaPlayer* the_player = new QMediaPlayer;
 static QPair<quint8, quint8>* the_rate = new QPair<quint8, quint8>{40, 0};
 return {the_player, the_rate};
}

int main(int argc, char *argv[])
{
 WCM_Database wcmd(CLO43SD_DB_CODE,
   DEFAULT_WCM_FOLDER "/dbs/test-" CLO43SD_DB_CODE ".wdb");
 wcmd.load();
 WCM_Column_Set wcs(wcmd);

 QString ds_root;

 // //  retrieve info
 {
  WCM_Hypernode whn;
  QByteArray qba;
  wcmd.retrieve_record(qba, "Default@Info");
  whn.absorb_data(qba, wcs);
  whn.with_hyponode(0) << [&wcmd](WCM_Hyponode& who)
  {
   wcmd.reinit_datetimes(who.qt_encoding());
  };
  whn.with_hyponode(1) << [&ds_root](WCM_Hyponode& who)
  {
   ds_root = who.qt_encoding().toString();
  };

  qDebug() << "Database Created: " << wcmd.datetimes()[WCM_Database::Created];
  qDebug() << "External Dataset Root: " << ds_root;
 }

 CLO_Database cdb(&wcmd);
 cdb.set_external_root_folder(ds_root);

 QDir audio_folder(DEFAULT_AUDIO_FOLDER);
 audio_folder.makeAbsolute();
 cdb.set_external_audio_folder(audio_folder.path());

 // // check species list
 {
  load_species(wcmd, wcs, cdb);
 }

 for(CLO_Species* sp : cdb.species_vec())
 {
  qDebug() << sp->abbreviation() << ": " << sp->name();

  // //  uncomment to generate the coefficient ntxh files
   //    run_species_convert(wcmd, wcs, sp->abbreviation(), ds_root);
 }


 QApplication qapp(argc, argv);

 ScignStage_Audio_TableModel tm(4, cdb.species_vec().size());

 tm.set_headers({"Abbreviation", "Name",
   "Number of Instances", "Current View Range"});

 tm.set_get_data_callback([&cdb](u4 args [3], QVariant& result)
 {
  if(args[2] != Qt::DisplayRole)
     return;
  CLO_Species* sp = cdb.species_vec()[args[0]];
  switch (args[1])
  {
  case 0: result.setValue(sp->abbreviation()); break;
  case 1: result.setValue(sp->name()); break;
  case 2: result.setValue(sp->instances()); break;
  case 3:
   {
    CLO_Species_Display_Info* cdi = cdb.get_display_info(sp);
    result.setValue(cdi->get_view_min_max_string());
   }
   break;
  default: break;
  }
 });


 ScignStage_Audio_Dialog dlg(nullptr);

 dlg.set_table_model(&tm);

 CLO_Species* current_species = nullptr;

 QObject::connect(&dlg,
     &ScignStage_Audio_Dialog::file_list_row_selected,
     [&cdb, &dlg, &current_species](int r, QString qs, QClipboard* clipboard)
 {
  if(!current_species)
    return;

  QString fp = cdb.map_audio_file_to_full_path(current_species, qs);
  if(clipboard)
    clipboard->setText(fp);
  else
  {
   qDebug() << "Playing: " << fp;
   QPair<QMediaPlayer*, QPair<quint8, quint8>*> pr = get_media_player();
   QMediaPlayer* player = pr.first;
   player->setMedia(QUrl::fromLocalFile(fp));
   player->setVolume(dlg.get_current_volume());
   *pr.second = {dlg.get_repeat_rate(), 0};
   qDebug() << "Will be Repeated: " << pr.second->first;
   QObject::connect(player, &QMediaPlayer::stateChanged,
           [player, pr]()
   {
    QMediaPlayer::State s = player->state();
    if(s == QMediaPlayer::StoppedState)
    {
     quint8& r = pr.second->second;
     ++r;
     if(r < pr.second->first)
       player->play();
    }
   });
   player->play();
  }
 });

 QObject::connect(&dlg,
   &ScignStage_Audio_Dialog::main_table_view_row_selected,
   [&cdb, &dlg, &current_species](int r)
 {
  CLO_Species* sp = cdb.species_vec().value(r);
  if(!sp)
    return;
  current_species = sp;

//?  dlg.set_current_species(sp);
//  qDebug() << "R: " << sp->name();

  QStringList qsl;
  cdb.get_files(sp, 10, qsl);

  dlg.redraw_file_list(qsl);
 });

// QSound audio(
//   "/home/nlevisrael/hypergr/ntxh/xd/clo43sd/CLO-43SD-AUDIO/audio/AMRE2330536360101.wav");
// audio.play();

// QString path = "/home/nlevisrael/hypergr/ntxh/xd/clo43sd/CLO-43SD-AUDIO/audio/AMRE2330536360101.wav";
// QMediaPlayer* player = new QMediaPlayer;
// player->setMedia(QUrl::fromLocalFile(path));
// player->setVolume(250);
// player->play();

 QObject::connect(&dlg, &ScignStage_Audio_Dialog::canceled,
   [&qapp]()
 {
  qDebug() << "Closing ...";
  qapp.exit();
 });

 dlg.show();
 qapp.exec();

// while(!audio.isFinished())
//  ;
 return 0;
}







int main3(int argc, char *argv[])
{
 WCM_Database wcmd("200", DEFAULT_WCM_FOLDER "/dbs/test-200.wdb");

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
// WCM_Database wcmd("100", DEFAULT_WCM_FOLDER "/dbs/test-100.wdb");

 NTXH_Document doc(DEFAULT_WCM_FOLDER "/species.ntxh");

 doc.parse();

 typedef NTXH_Graph::hypernode_type hypernode_type;

//? NTXH_Graph& g = *doc.graph();

 QVector<CLO_Species*> species;

 QVector<NTXH_Graph::hypernode_type*>& hns = doc.top_level_hypernodes();

 QMap<u4, QString> icm;
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

 WCM_Database wcmd("200", DEFAULT_WCM_FOLDER "/dbs/test-200.wdb");
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

int main5(int argc, char *argv[])
{
 WCM_Database wcmd("200", DEFAULT_WCM_FOLDER "/dbs/test-200.wdb");
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

 with_files(QDir(ds_root + "/mfcc")).filter({"*.npy"}) << [](QFileInfo& qfi)
 {
  qDebug() << qfi.absoluteFilePath();
 };
 return 0;
}

int main11(int argc, char *argv[])
{
 WCM_Database wcmd("200", DEFAULT_WCM_FOLDER "/dbs/test-200.wdb");
 wcmd.load();

 WCM_Column_Set qwcs(wcmd);

// WCM_Hypernode whn;

 QByteArray qba;

// wcmd.retrieve_record(qba, "Default@Species", "Species::Abbreviation",
//  "BTBW"_q);

 QMap<u4, QString> icm;
 icm[0] = "Species::Abbreviation";

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
//  u4 num = qv.toInt();
//  qDebug() << num;
// };

// whn.with_hyponode(2) << [](WCM_Hyponode& who)
// {
//  QVariant qv = who.qt_encoding();
//  QString qs = qv.toString();
//  qDebug() << qs;
// };


 wcmd.for_all_records("Default@CLO_File", "Species::Abbreviation@CLO_File",
   "BTBW"_q) << [&qwcs, &wcmd](QByteArray& qba, void*)
 {
  QMap<u4, QString> icm;
  icm[1] = "Species::Abbreviation@CLO_File";
  WCM_Hypernode whn;

  whn.set_indexed_column_map(&icm);
  whn.absorb_data(qba, qwcs);

  whn.with_hyponode(0) << [&wcmd](WCM_Hyponode& who)
  {
   QVariant qv = who.qt_encoding();
   u1 num = qv.toInt();
   qDebug() << num;
  };

  whn.with_hyponode(1) << [&wcmd](WCM_Hyponode& who)
  {
   wg_int wgi = who.wgdb_encoding().data;
   QString abbr = wcmd.wdb().decode_string(wgi);
   qDebug() << abbr;
  };

  whn.with_hyponode(2) << [](WCM_Hyponode& who)
  {
   QVariant qv = who.qt_encoding();
   QString qs = qv.toString();
   qDebug() << qs;
  };
 };

 QVector<QPair<QByteArray*, void*>> matches;

 wcmd.retrieve_all_records("Default@CLO_File", "Species::Abbreviation@CLO_File",
   "BTBW"_q, matches);

 for(QPair<QByteArray*, void*> pr : matches)
 {
  QMap<u4, QString> icm;
  icm[1] = "Species::Abbreviation@CLO_File";
  WCM_Hypernode whn;

  whn.set_indexed_column_map(&icm);
  whn.absorb_data(*pr.first, qwcs);

  whn.with_hyponode(0) << [&wcmd](WCM_Hyponode& who)
  {
   QVariant qv = who.qt_encoding();
   u1 num = qv.toInt();
   qDebug() << num;
  };

  whn.with_hyponode(1) << [&wcmd](WCM_Hyponode& who)
  {
   wg_int wgi = who.wgdb_encoding().data;
   QString abbr = wcmd.wdb().decode_string(wgi);
   qDebug() << abbr;
  };

  whn.with_hyponode(2) << [](WCM_Hyponode& who)
  {
   QVariant qv = who.qt_encoding();
   QString qs = qv.toString();
   qDebug() << qs;
  };
 }

 return 0;

}

int main7(int argc, char *argv[])
{
 WCM_Database wcmd("200", DEFAULT_WCM_FOLDER "/dbs/test-200.wdb");
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

 QMap<u4, QString> icm;
 icm[1] = "Species::Abbreviation@CLO_File";

 QByteArray qba;
 wcmd.retrieve_record(qba, "Default@CLO_File", "Species::Abbreviation@CLO_File",
    "BTBW"_q);

 WCM_Hypernode whn;

 whn.set_indexed_column_map(&icm);
 whn.absorb_data(qba, qwcs);

 whn.with_hyponode(0) << [](WCM_Hyponode& who)
 {
  QVariant qv = who.qt_encoding();
  u1 num = (u1) qv.toInt();
  qDebug() << num;
 };

 whn.with_hyponode(1) << [&wcmd](WCM_Hyponode& who)
 {
  wg_int wgi = who.wgdb_encoding().data;
  QString abbr = wcmd.wdb().decode_string(wgi);
  qDebug() << abbr;
 };

 whn.with_hyponode(2) << [](WCM_Hyponode& who)
 {
  QVariant qv = who.qt_encoding();
  QString qs = qv.toString();
  qDebug() << qs;
 };

 return 0;
}

int main6(int argc, char *argv[])
{
 WCM_Database wcmd("200", DEFAULT_WCM_FOLDER "/dbs/test-200.wdb");
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

 QMap<u4, QString> icm;
 icm[0] = "Species::Abbreviation";

 QVector<CLO_Species*> species_vec;
 QMap<QString, CLO_Species*> species_map;
 QMap<CLO_Species*, CLO_File*> species_files;

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

// CLO_Species* current_species = nullptr;
// CLO_File* current_species_file = nullptr;
// QString current_abbreviation;

 QMap<u4, QString> ficm;
 ficm[1] = "Species::Abbreviation@CLO_File";

 auto process_files = [&wcmd, &ficm](QFileInfo& qfi, CLO_File::Kinds k)
 {
  QString bn = qfi.baseName();
  CLO_File species_file(k);
  species_file.set_abbreviation(bn.left(4));
  bn.remove(0, 4);
  species_file.set_tail(bn);
  wcmd.with_new_hyponode_array(3) << [&species_file, &wcmd, &ficm]
    (WCM_WhiteDB& wdb, WCM_Hyponode** whos)
  {
   WCM_Hypernode whn;
   whos[0]->set_qt_encoding((u1)species_file.kind());
   whos[1]->set_wgdb_encoding({wdb.encode_string(species_file.abbreviation())});
   whos[2]->set_qt_encoding(species_file.tail());
   whn.add_hyponodes(whos)[3];
   whn.set_indexed_column_map(&ficm);
   whn.add_to_database(wcmd, "@CLO_File", "Default@CLO_File");
  };
 };

 with_files(QDir(ds_root + "/logmelspec")).filter({"*.npy"}) <<
   [process_files](QFileInfo& qfi)
 {
  process_files(qfi, CLO_File::Kinds::Logmelspec);
 };

 with_files(QDir(ds_root + "/mfcc")).filter({"*.npy"}) <<
   [process_files](QFileInfo& qfi)
 {
  process_files(qfi, CLO_File::Kinds::Logmelspec);
 };

// with_files(QDir(ds_root + "/mfcc2")).filter({"*.npy"}) <<
//   [process_files](QFileInfo& qfi)
// {
//  process_files(qfi, CLO_File::Kinds::Logmelspec);
// };

// with_map(species_map) << [](QString abbreviation, CLO_Species* clo)
// {
//  qDebug() << abbreviation;
// };


// for(u4 i = 1; i <= species_count; ++i)
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
//   u4 num = qv.toInt();
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
//  u4 num = qv.toInt();
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
// //    (WCM_WhiteDB& wdb, WCM_Hyponode* who, u4 index)
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

//// // test some specific species
//{
// // //  first get species info ...
// {
//  QMap<u4, QString> icm;
//  icm[0] = "Species::Abbreviation";

//  QByteArray qba;
//  wcmd.retrieve_record(qba, "Default@Species", "Species::Abbreviation",
//     "BTBW"_q);

//  WCM_Hypernode whn;

//  whn.set_indexed_column_map(&icm);
//  whn.absorb_data(qba, wcs);

//  whn.with_hyponode(0) << [&wcmd](WCM_Hyponode& who)
//  {
//   wg_int wgi = who.wgdb_encoding().data;
//   QString abbr = wcmd.wdb().decode_string(wgi);
//   qDebug() << "Species Abbreviation: " << abbr;
//  };

//  whn.with_hyponode(1) << [](WCM_Hyponode& who)
//  {
//   QVariant qv = who.qt_encoding();
////    u1 num = (u1) qv.toInt();
//   qDebug() << "Number of Instances: " << (u1) qv.toInt();
//  };

//  whn.with_hyponode(2) << [](WCM_Hyponode& who)
//  {
//   QVariant qv = who.qt_encoding();
////    QString qs = qv.toString();
//   qDebug() << "Species Name: " << qv.toString();
//  };
// }
//}
