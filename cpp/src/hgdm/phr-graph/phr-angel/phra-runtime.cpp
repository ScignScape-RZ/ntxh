
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phra-runtime.h"

#include "phra-graph-build.h"


PHRA_Runtime::PHRA_Runtime()
  :  current_context_(nullptr),
     ref_count_(0)
{
}

void PHRA_Runtime::add_ref()
{
 // Increase the reference counter
 ref_count_++;
}
 
void PHRA_Runtime::release()
{
 // Decrease ref count and delete if it reaches 0
 if( --ref_count_ == 0 )
   delete this;
}


