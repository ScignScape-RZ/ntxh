
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef CLO_SPECIES__H
#define CLO_SPECIES__H


#include "phaong/phaong.h"
#include "phaong/phaong-types.h"

#include "global-types.h"

#include "kans.h"
#include "accessors.h"

#include <QVector>
#include <QString>

class QTextStream;

//class WCM_Hyponode;
//class WCM_Database;

class CLO_Species
{
 QString abbreviation_;
 u4 instances_;
 QString name_;


public:

 CLO_Species();

 ACCESSORS(QString ,abbreviation)
 ACCESSORS(u4 ,instances)
 ACCESSORS(QString ,name)


};


#endif // CLO_SPECIES__H
