
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phra-runtime-context.h"

#include "phra-binary-channel.h"

PHRA_Value_Context::PHRA_Value_Context()
  :  ref_count_(0)
{
}

void PHRA_Value_Context::merge_binary_channel(PHRA_Binary_Channel* pbc, u1 length, u8 mask)
{
 //qDebug() << "PBC k is " << pbc->kind();
 u8 index = 1;
 for(int i = 0; i < length; ++i)
 {
  u1 m = mask & 3;
  mask >>= 2;
  switch(m)
  {
  case 0: 
   u1s_.push_back(pbc->extract_1(index));
   index += 1;
   break;
  case 1: 
   u2s_.push_back(pbc->extract_2(index));
   index += 2;
   break;
  case 2: 
   u4s_.push_back(pbc->extract_4(index));
   index += 4;
   break;
  case 3: 
   u8s_.push_back(pbc->extract_8(index));
   index += 8;
   break;
  }
 } 
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


