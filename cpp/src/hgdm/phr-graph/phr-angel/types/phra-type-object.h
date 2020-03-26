
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef PHRA_TYPE_OBJECT__H
#define PHRA_TYPE_OBJECT__H

#include <QDebug>
#include <QVector>
#include <QString>
#include <QByteArray>

#include "angelscript.h"

#include "rzns.h"
#include "flags.h"

#include "global-types.h"

#include "accessors.h"


class PHRA_Type_Object
{
public:

 flags_(1)
  bool constant:1;
  bool pointer:1;
  bool reference:1;
  bool nullable:1;
  bool defaultive:1;
  bool constructive:1;
  bool split_ground_or_casts:1;
 _flags
 

private:

 QString name_;
 void* ground_or_casts_;

 u1 byte_length_;
 u1 byte_length_code_;
 
public:

 PHRA_Type_Object(); 

 ACCESSORS(QString ,name)
 ACCESSORS(u1 ,byte_length)
 ACCESSORS(u1 ,byte_length_code)


};


#endif //  PHRA_TYPE_OBJECT__H

