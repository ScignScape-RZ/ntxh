
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "clo-database.h"

#include "clo-species.h"
#include "clo-file.h"

#include <QDir>

CLO_Database::CLO_Database()
{

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
