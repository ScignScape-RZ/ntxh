
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHRA_RUNTIME__H
#define PHRA_RUNTIME__H

#include <QDebug>
#include <QFile>

#include "angelscript.h"

#include "rzns.h"

RZNS_CLASS_DECLARE(PhrGraphCore ,PHR_Graph)
RZNS_CLASS_DECLARE(PhrGraphCore ,PHR_Graph_PHR_Output)

RZNS_CLASS_DECLARE(PhrGraphCore ,PHR_Graph_Frame)
RZNS_CLASS_DECLARE(PhrGraphCore ,PHR_Graph_Query)

USING_RZNS(PhrGraphCore)

class PHRA_Graph_Build;

class PHRA_Runtime_Context;

class PHRA_Runtime
{
 PHRA_Runtime_Context* current_context_;

 int ref_count_;
 
public:

 PHRA_Runtime(); 

 void add_ref();
 void release();
};


#endif //  PHRA_RUNTIME__H

