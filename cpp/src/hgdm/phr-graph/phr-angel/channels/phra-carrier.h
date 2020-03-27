
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef PHRA_CARRIER__H
#define PHRA_CARRIER__H

#include <QDebug>
#include <QVector>
#include <QString>
#include <QByteArray>

#include "angelscript.h"

#include "rzns.h"
#include "flags.h"

#include "global-types.h"

#include "accessors.h"


class PHRA_Carrier
{
public:

 flags_(1)
   bool constant:1;
   bool write_only:1;
   bool write_mandatory:1;
   bool split_type_or_context:1;
   bool full_symbol_info:1;
   bool encoded_symbol_name:1;
 _flags

private:

 u1 locator_;

 void* type_or_context_;
 u8 symbol_encoding_;
 
public:

 PHRA_Carrier();

 ACCESSORS(u1 ,locator)

 void encode_symbol_name(QString name);

 QString get_symbol_name();

};


#endif //  PHRA_CARRIER__H

