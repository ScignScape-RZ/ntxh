
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHRA_VALUE_CONTEXT__H
#define PHRA_VALUE_CONTEXT__H

#include <QDebug>
#include <QVector>
#include <QString>

#include "angelscript.h"

#include "rzns.h"
#include "flags.h"

#include "global-types.h"

class PHRA_Binary_Channel;

class PHRA_Value_Context
{
 QVector<u1> u1s_;
 QVector<u2> u2s_;

 QVector<u4> u4s_;
 QVector<u8> u8s_;

 QVector<QString> strs_;

 int ref_count_;
 
public:

 PHRA_Value_Context(); 

 void merge_binary_channel(PHRA_Binary_Channel* pbc, 
   u1 length, u8 mask); 

 void locator_to_binary(PHRA_Binary_Channel& pbc, u1 locator);

 u1 get1v(u1 locator);
 u2 get2v(u1 locator);
 u4 get4v(u1 locator);
 u8 get8v(u1 locator);

 u1 loc1(u1 value);
 u1 loc2(u2 value);
 u1 loc4(u4 value);
 u1 loc8(u8 value);

 void add_ref();
 void release();
};


#endif //  PHRA_VALUE_CONTEXT__H

