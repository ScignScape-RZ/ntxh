
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHRA_RUN_CONTEXT__H
#define PHRA_RUN_CONTEXT__H

#include <QDebug>
#include <QFile>

#include "angelscript.h"

#include "rzns.h"

RZNS_CLASS_DECLARE(PhrGraphCore ,PHR_Graph)
RZNS_CLASS_DECLARE(PhrGraphCore ,PHR_Graph_PHR_Output)

RZNS_CLASS_DECLARE(PhrGraphCore ,PHR_Graph_Frame)
RZNS_CLASS_DECLARE(PhrGraphCore ,PHR_Graph_Query)

USING_RZNS(PhrGraphCore)


class PHRA_Run_Context
{
 PHR_Graph* phr_graph_;

 PHR_Graph_PHR_Output* phr_out_;

 PHR_Graph_Frame& fr_;
 const PHR_Graph_Query& qy_;

 int ref_count_;
 
public:

 PHRA_Run_Context(); 

 void init_graph();

 void add_ref();
 void release();
};


#endif //  PHRA_RUN_CONTEXT__H

