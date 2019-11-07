
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "clo-database.h"

#include "clo-species.h"
#include "clo-file.h"

#include "clo-species-display-info.h"

#include "wcm/wcm-database.h"
#include "wcm/wcm-hypernode.h"
#include "wcm/wcm-column-set.h"
#include "wcm/wcm-hyponode.h"

#include <QDir>

CLO_Database::CLO_Database(WCM_Database* wcm_database)
  :  wcm_database_(wcm_database)
{

}

QString CLO_Database::map_audio_file_to_full_path(CLO_Species* sp, QString file)
{
 static QString pattern{"%1/%2%3.wav"};
 return pattern.arg(external_audio_folder_)
   .arg(sp->abbreviation()).arg(file);
}


void CLO_Database::get_files(CLO_Species* sp, u1 num, QStringList& qsl)
{
 CLO_Species_Display_Info* cdi = get_display_info(sp);
 cdi->check_view_minimum();

// WCM_Column* wcmc;

 if(!cdi->cursor().first)
 {
  QPair<u8, u8> qq = wcm_database_->construct_query_cursor(// "Default@CLO_File",
    "Species::Abbreviation@CLO_File",
    sp->abbreviation());
  if(!qq.first)
    return;
  cdi->set_cursor(qq);
 }
 for(int i = 0; i < 10; ++i)
 {
  QByteArray qba;// = new QByteArray;
  void* nr;
  wcm_database_->retrieve_next_record("Default@CLO_File",
    //"Species::Abbreviation@CLO_File",
    (WCM_Column*) cdi->cursor().first,
    (wg_query*) cdi->cursor().second, {&qba, nr});
  if(qba.isEmpty())
    return;
  {
   WCM_Hypernode whn;
   QMap<u4, QString> icm;
   icm[1] = "Species::Abbreviation@CLO_File";
   whn.set_indexed_column_map(&icm);
   WCM_Column_Set wcs(*wcm_database_);
   whn.absorb_data(qba, wcs);

   QString tail;
   whn.with_hyponode(2) << [&tail](WCM_Hyponode& who)
   {
    QVariant qv = who.qt_encoding();
    tail = who.qt_encoding().toString();
   };
   qsl.push_back(tail);
  };
 }

#ifdef HIDE
// for(int i = 0; i < 10; ++i)
//   qsl.push_back(QString("X%1").arg(i));
// u4 count = 0;
 wcm_database_->for_all_records("Default@CLO_File", "Species::Abbreviation@CLO_File",
   sp->abbreviation()) << [this, num, &qsl](QByteArray& qba, void*, u4 count,
      brake brk)
 {
  WCM_Hypernode whn;
  QMap<u4, QString> icm;
  icm[1] = "Species::Abbreviation@CLO_File";
  whn.set_indexed_column_map(&icm);
  WCM_Column_Set wcs(*wcm_database_);
  whn.absorb_data(qba, wcs);

  QString tail;



//  QString abbr = "BTBW"_q;
//  QString tail;

//  CLO_File* cf = new CLO_File;
////  cf->set_abbreviation(abbr);

//  whn.with_hyponode(0) << [cf](WCM_Hyponode& who)
//  {
//   qDebug() << "File Kind: " << CLO_File::kind_string(who.qt_encoding().toInt());
//   cf->set_kind((CLO_File::Kinds) who.qt_encoding().toInt());
//  };

  whn.with_hyponode(2) << [&tail](WCM_Hyponode& who)
  {
   QVariant qv = who.qt_encoding();
   tail = who.qt_encoding().toString();
//   qDebug() << "File Tail: " << tail;
//   cf->set_tail(tail);
  };

  qsl.push_back(tail);

 };
#endif //def HIDE
}


CLO_File* CLO_Database::get_conversion_file(CLO_File& cf)
{
 CLO_File* result = cf.conversion_file();
 if(!result)
 {
  QDir qd(external_root_folder_);
  QString file_path;
  switch (cf.kind())
  {
  case CLO_File::Kinds::NPY_Logmelspec:
   qd.cd("../lph");
   qd.cd(cf.abbreviation());
   //result->
   file_path = qd.absoluteFilePath(QString("ph-%1%2.logmelspec.ntxh")
     .arg(cf.abbreviation()).arg(cf.tail()));
   break;
  case CLO_File::Kinds::NPY_MFCC:
   qd.cd("../mph");
   qd.cd(cf.abbreviation());
   //result->
   file_path = qd.absoluteFilePath(QString("ph-%1%2.mfcc.ntxh")
     .arg(cf.abbreviation()).arg(cf.tail()));
   break;
  default:
   break;
  }

  if(!file_path.isEmpty())
  {
   result = new CLO_File;
   result->set_absolute_path(file_path);
   cf.set_conversion_file(result);
  }
 }
 return result;
}

CLO_Species_Display_Info* CLO_Database::get_display_info(CLO_Species* sp)
{
 CLO_Species_Display_Info* result;
 auto it = display_info_map_.find(sp);
 if(it == display_info_map_.end())
 {
  result = new CLO_Species_Display_Info;
  display_info_map_[sp] = result; 
 }
 else
   result = *it;
 return result;
}


void CLO_Database::check_species_folders()
{
 if(external_root_folder_.isEmpty())
   return;
 QDir qd = QDir(external_root_folder_);
 if(!qd.cdUp())
   return;
 for(CLO_Species* s : species_vec_)
 {
  qd.cd("lph");
  qd.mkdir(s->abbreviation());
  qd.cdUp();
  qd.cd("mph");
  qd.mkdir(s->abbreviation());
  qd.cdUp();
 }
}
