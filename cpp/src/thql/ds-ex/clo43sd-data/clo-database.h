
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

//class WCM_Hyponode;
//class WCM_Database;

class CLO_Database
{
 QVector<CLO_Species*> species_vec_;
 QMap<QString, CLO_Species*> species_map_;

 QString external_root_folder_;

public:

 CLO_Database();

 ACCESSORS__RGET(QVector<CLO_Species*> ,species_vec)
 ACCESSORS__RGET(MACRO_PASTE(QMap<QString, CLO_Species*>) ,species_map)

 ACCESSORS(QString ,external_root_folder)

 void check_species_folders();

 CLO_File* get_conversion_file(CLO_File& cf);


};


#endif // CLO_DATABASE__H
