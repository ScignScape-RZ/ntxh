
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phra-symbol-context.h"

#include "channels/phra-binary-channel.h"


PHRA_Symbol_Context::PHRA_Symbol_Context()
  :  ref_count_(0)
{
}

void PHRA_Symbol_Context::add_ref()
{
 // Increase the reference counter
 ref_count_++;
}
 
void PHRA_Symbol_Context::release()
{
 // Decrease ref count and delete if it reaches 0
 if( --ref_count_ == 0 )
   delete this;
}



