
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phra-value-context.h"

#include "channels/phra-binary-channel.h"

PHRA_Value_Context::PHRA_Value_Context()
  :  ref_count_(0)
{
}

u1 PHRA_Value_Context::loc1(u1 value)
{
 u1s_.push_back(value);
 return (u1s_.size() << 2);
}

u1 PHRA_Value_Context::loc2(u2 value)
{
 u2s_.push_back(value);
 return (u2s_.size() << 2) | 1;
}

u1 PHRA_Value_Context::loc4(u4 value)
{
 u4s_.push_back(value);
 return (u4s_.size() << 2) | 2;
}

u1 PHRA_Value_Context::loc8(u8 value)
{
 u8s_.push_back(value);
 return (u8s_.size() << 2) | 3;
}

void PHRA_Value_Context::locator_to_binary(PHRA_Binary_Channel& pbc, u1 locator)
{
 switch(locator & 3)
 {
 case 0: pbc.append( u1s_[(locator >> 2) - 1] ); break;
 case 1: pbc.append( u2s_[(locator >> 2) - 1] ); break;
 case 2: pbc.append( u4s_[(locator >> 2) - 1] ); break;
 case 3: pbc.append( u8s_[(locator >> 2) - 1] ); break;
 } 
}

u1 PHRA_Value_Context::get1v(u1 locator)
{
 switch(locator & 3)
 {
 case 0: return u1s_[(locator >> 2) - 1];
 case 1: return get2v(locator);
 case 2: return get4v(locator);
 case 3: return get8v(locator);
 }
}

u2 PHRA_Value_Context::get2v(u1 locator)
{
 switch(locator & 3)
 {
 case 0: return get1v(locator); 
 case 1: return u2s_[(locator >> 2) - 1];
 case 2: return get4v(locator);
 case 3: return get8v(locator);
 }
}

u4 PHRA_Value_Context::get4v(u1 locator)
{
 switch(locator & 3)
 {
 case 0: return get1v(locator); 
 case 1: return get2v(locator);
 case 2: return u4s_[(locator >> 2) - 1];
 case 3: return get8v(locator);
 }
}

u8 PHRA_Value_Context::get8v(u1 locator)
{
 switch(locator & 3)
 {
 case 0: return get1v(locator); 
 case 1: return get2v(locator);
 case 2: return get4v(locator);
 case 3: return u8s_[(locator >> 2) - 1];
 }
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


