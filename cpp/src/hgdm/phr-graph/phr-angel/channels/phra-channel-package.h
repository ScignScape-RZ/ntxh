
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHRA_CHANNEL_PACKAGE__H
#define PHRA_CHANNEL_PACKAGE__H

#include <QDebug>
#include <QVector>
#include <QString>
#include <QList>

#include "angelscript.h"

#include "rzns.h"

#include "global-types.h"

#include "accessors.h"

class PHRA_Carrier_Channel;

class PHRA_Channel_Package : QList<PHRA_Carrier_Channel*>
{
 QString fname_;

 int ref_count_;

public:

 PHRA_Channel_Package(); 

 ACCESSORS(QString ,fname)

 PHRA_Carrier_Channel* add_carrier_channel(QString kind);

 void add_fname(const std::string& name);

 void add_ref();
 void release();

};


#endif //  PHRA_CHANNEL_PACKAGE__H

