
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef PHRA_TYPE_SYSTEM__H
#define PHRA_TYPE_SYSTEM__H

#include <QDebug>
#include <QVector>
#include <QString>
#include <QByteArray>

#include "angelscript.h"

#include "rzns.h"

#include "global-types.h"

#include "accessors.h"

class PHRA_Type_Object;

class PHRA_Type_System
{
 QMap<QString, PHRA_Type_Object*> type_objects_;

public:

 PHRA_Type_System(); 
};


#endif //  PHRA_TYPE_SYSTEM__H

