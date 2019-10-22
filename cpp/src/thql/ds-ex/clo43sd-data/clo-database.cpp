
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "clo-database.h"

#include "clo-species.h"

#include <QDir>

CLO_Database::CLO_Database()
{

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
