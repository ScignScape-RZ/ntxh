
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHRA_RUNTIME_CONTEXT__H
#define PHRA_RUNTIME_CONTEXT__H

#include <QDebug>
#include <QVector>
#include <QString>

#include "angelscript.h"

#include "rzns.h"

#include "global-types.h"

RZNS_CLASS_DECLARE(PhrGraphCore ,PHR_Graph)
RZNS_CLASS_DECLARE(PhrGraphCore ,PHR_Graph_PHR_Output)

RZNS_CLASS_DECLARE(PhrGraphCore ,PHR_Graph_Frame)
RZNS_CLASS_DECLARE(PhrGraphCore ,PHR_Graph_Query)

USING_RZNS(PhrGraphCore)

class PHRA_Graph_Build;

class PHRA_Runtime_Context
{
 QVector<u4> u4s_;
 QVector<u8> u8s_;
 QVector<QString> strs_;

 int ref_count_;
 
public:

 PHRA_Runtime_Context(); 

 void add_ref();
 void release();
};


#endif //  PHRA_RUNTIME_CONTEXT__H

