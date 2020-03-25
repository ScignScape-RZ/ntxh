
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phra-runtime-context.h"

#include "phra-graph-build.h"

PHRA_Value_Context::PHRA_Value_Context()
  :  ref_count_(0)
{
}

void PHRA_Value_Context::add_ref()
{
 // Increase the reference counter
 ref_count_++;
}
 
void PHRA_Value_Context::release()
{
 // Decrease ref count and delete if it reaches 0
 if( --ref_count_ == 0 )
   delete this;
}


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





PHRA_Runtime_Context::PHRA_Runtime_Context()
  :  ref_count_(0), values_(nullptr), symbols_(nullptr)
{
}

PHRA_Value_Context* PHRA_Runtime_Context::init_value_context()
{
 values_ = new PHRA_Value_Context;
 return values_; 
}

PHRA_Symbol_Context* PHRA_Runtime_Context::init_symbol_context()
{
 symbols_ = new PHRA_Symbol_Context;
 return symbols_; 
}


void PHRA_Runtime_Context::add_ref()
{
 // Increase the reference counter
 ref_count_++;
}
 
void PHRA_Runtime_Context::release()
{
 // Decrease ref count and delete if it reaches 0
 if( --ref_count_ == 0 )
   delete this;
}


