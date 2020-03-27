
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef PHRA_FUNCTION_TABLE__H
#define PHRA_FUNCTION_TABLE__H

#include <QDebug>
#include <QString>
#include <QMap>

#include "accessors.h"

#include "global-types.h"

class PHRA_Binary_Channel;



class PHRA_Function_Table
{
 typedef u2 u16t;
 typedef u4 u32t;

 friend class PHRA_Channel_Runner;
 typedef void(*_s0a_fn1_16_32_type)(u16t, u32t);

 QMap<QString, _s0a_fn1_16_32_type> fns_;

public:

 PHRA_Function_Table(); 

 void add_fn(QString name, _s0a_fn1_16_32_type val);
 _s0a_fn1_16_32_type get_fn(QString name);

};


#endif //  PHRA_CHANNEL_RUNNER__H

