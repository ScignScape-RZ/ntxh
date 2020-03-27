
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phra-run-context.h"

#include "phra-graph-build.h"


PHRA_Run_Context::PHRA_Run_Context()
  : //? phra_graph_build_(nullptr),
     ref_count_(0)
{
}

void PHRA_Run_Context::add_ref()
{
 // Increase the reference counter
 ref_count_++;
}
 
void PHRA_Run_Context::release()
{
 // Decrease ref count and delete if it reaches 0
 if( --ref_count_ == 0 )
   delete this;
}

//PHRA_Graph_Build* PHRA_Run_Context::init_graph()
//{
// phra_graph_build_ = new PHRA_Graph_Build;
// phra_graph_build_->init_graph();
// return phra_graph_build_;
//}


