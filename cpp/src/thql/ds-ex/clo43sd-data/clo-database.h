
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef CLO_DATABASE__H
#define CLO_DATABASE__H


#include "phaong/phaong.h"
#include "phaong/phaong-types.h"

#include "global-types.h"

#include "kans.h"
#include "accessors.h"

#include <QVector>
#include <QString>
#include <QMap>


class CLO_Species;
class CLO_File;

class CLO_Species_Display_Info;

//class WCM_Hyponode;
//
class WCM_Database;

class CLO_Database
{
 QVector<CLO_Species*> species_vec_;
 QMap<QString, CLO_Species*> species_map_;

 QString external_root_folder_;
 QString external_audio_folder_;

 WCM_Database* wcm_database_;

 QMap<CLO_Species*, CLO_Species_Display_Info*> display_info_map_; 

public:

 CLO_Database(WCM_Database* wcm_database);

 ACCESSORS__RGET(QVector<CLO_Species*> ,species_vec)
 ACCESSORS__RGET(MACRO_PASTE(QMap<QString, CLO_Species*>) ,species_map)

 ACCESSORS(QString ,external_root_folder)
 ACCESSORS(QString ,external_audio_folder)

 ACCESSORS(WCM_Database* ,wcm_database)


 void check_species_folders();

 CLO_File* get_conversion_file(CLO_File& cf);
  
 CLO_Species_Display_Info* get_display_info(CLO_Species*);

 void get_files(CLO_Species* sp, u1 num, QStringList& qsl);

 QString map_audio_file_to_full_path(CLO_Species* sp, QString file);

};


#endif // CLO_DATABASE__H
