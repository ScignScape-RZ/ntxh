
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

class PHRA_Carrier_Channel : QVector<PHRA_Carrier*>
{
 QString kind_;

public:

 PHRA_Carrier_Channel(); 

 ACCESSORS(QString ,kind)

};


#endif //  PHRA_CARRIER_CHANNEL__H

