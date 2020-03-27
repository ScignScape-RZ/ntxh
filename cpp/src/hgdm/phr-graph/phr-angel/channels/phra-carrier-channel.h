
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef PHRA_CARRIER_CHANNEL__H
#define PHRA_CARRIER_CHANNEL__H

#include <QDebug>
#include <QVector>
#include <QString>
#include <QByteArray>

#include "angelscript.h"

#include "rzns.h"

#include "global-types.h"

#include "accessors.h"

class PHRA_Carrier;
class PHRA_Binary_Channel;
class PHRA_Value_Context;

class PHRA_Carrier_Channel : QVector<PHRA_Carrier*>
{
 QString kind_;

 int ref_count_;

public:

 PHRA_Carrier_Channel(QString kind); 

 ACCESSORS(QString ,kind)

 void add_carrier(const std::string& type_name, 
   const std::string& symbol_name, u1 locator); 

 PHRA_Binary_Channel* to_binary(PHRA_Value_Context* pvc);

 void add_ref();
 void release();


};


#endif //  PHRA_CARRIER_CHANNEL__H

