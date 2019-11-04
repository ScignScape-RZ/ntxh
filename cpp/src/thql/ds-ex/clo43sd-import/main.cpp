
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

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

#include "clo43sd-data/clo-file.h"
#include "clo43sd-data/clo-species.h"
#include "clo43sd-data/clo-database.h"

#include "ntxh-parser/ntxh-document.h"

#include "kans.h"

void create(WCM_Database& wcmd)
{
 wcmd.create_new_column("@Info");
 wcmd.create_new_singleton_column("Default@Info");

 wcmd.create_new_column("@Species");
 wcmd.create_new_column("Default@Species");
 wcmd.create_new_column("Species::Abbreviation");

 wcmd.create_new_column("@CLO_File");
 wcmd.create_new_column("Default@CLO_File");
 wcmd.create_new_column("Species::Abbreviation@CLO_File");

 wcmd.save();
}


int main(int argc, char *argv[])
{
 WCM_Database wcmd(CLO43SD_DB_CODE,
   DEFAULT_WCM_FOLDER "/dbs/test-" CLO43SD_DB_CODE ".wdb");

// wcmd.with_check_create() << &create;

 wcmd.with_check_create() << [&wcmd]()
 {
  wcmd.create_new_column("@Info");
  wcmd.create_new_singleton_column("Default@Info");

  wcmd.create_new_column("@Species");
  wcmd.create_new_column("Default@Species");
  wcmd.create_new_column("Species::Abbreviation");

  wcmd.create_new_column("@CLO_File");
  wcmd.create_new_column("Default@CLO_File");
  wcmd.create_new_column("Species::Abbreviation@CLO_File");

  wcmd.save();
 };

 wcmd.set_creation_datetime();

 // // init info hypernode
 {
  WCM_Hypernode whn;

  wcmd.with_new_hyponode_array(2) << [&wcmd, &whn](WCM_Hyponode** whos)
  {
   whos[0]->set_qt_encoding(wcmd.datetimes_qvariantmap());
   whos[1]->set_qt_encoding(CLO43SD_ROOT_FOLDER ""_q);
   whn.add_hyponodes(whos)[2];
   whn.add_to_database(wcmd, "@Info", "Default@Info");
  };
 }

 // // write species to database
 {
  NTXH_Document doc(DEFAULT_NTXH_FOLDER "/clo43sd/species.ntxh");
  doc.parse();
  CLO_Database cld(nullptr);
  cld.set_external_root_folder(CLO43SD_ROOT_FOLDER);
  QVector<CLO_Species*>& species = cld.species_vec();
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
  cld.check_species_folders();
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
 }

 // // write all files' paths to database
 {
  QMap<u4, QString> ficm;
  ficm[1] = "Species::Abbreviation@CLO_File";

  //
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

  with_files(QDir(CLO43SD_ROOT_FOLDER "/logmelspec")).filter({"*.npy"}) <<
    [process_files](QFileInfo& qfi)
  {
   process_files(qfi, CLO_File::Kinds::NPY_Logmelspec);
  };

  with_files(QDir(CLO43SD_ROOT_FOLDER "/mfcc")).filter({"*.npy"}) <<
    [process_files](QFileInfo& qfi)
  {
   process_files(qfi, CLO_File::Kinds::NPY_MFCC);
  };
 }

 return 0;
}

