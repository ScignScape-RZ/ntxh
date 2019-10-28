
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

 u4 current_view_minimum_;
 u4 current_view_maximum_;

 static u2 view_offset;

public:

 CLO_Species();

 ACCESSORS(QString ,abbreviation)
 ACCESSORS(u4 ,instances)
 ACCESSORS(QString ,name)

 QString get_view_min_max_string();

 void reset_view_minimum(u4 m)
 {
  current_view_minimum_ = m;
  current_view_maximum_ = m + view_offset - 1;
 }

 void reset_view_minimum()
 {
  current_view_minimum_ = 0;
  current_view_maximum_ = 0;
 }

 QPair<u4, u4> get_view_range();

};


#endif // CLO_SPECIES__H
