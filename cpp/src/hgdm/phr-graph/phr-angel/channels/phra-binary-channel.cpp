
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phra-binary-channel.h"


PHRA_Binary_Channel::PHRA_Binary_Channel()
  :  ref_count_(0), mask_(0)
{
}

void PHRA_Binary_Channel::test_extract_1(u2 index)
{
 u1 value = (u1)values_[index - 1];
 qDebug() << "Value is: " << value;

}

u1 PHRA_Binary_Channel::extract_1(u2 index)
{
 return (u1)values_[index - 1];
}


void PHRA_Binary_Channel::test_extract_2(u2 index)
{
 u2 value = 0;
 value |= (u2)(u1)values_[index - 1];
 value |= ( ((u2)(u1)values_[index]) << 8); 

 qDebug() << "Value is: " << value;
}

u2 PHRA_Binary_Channel::extract_2(u2 index)
{
 return ((u2)(u1)values_[index - 1])
   | (( ((u2)(u1)values_[index]) << 8)); 

}

void PHRA_Binary_Channel::test_extract_4(u2 index)
{
 u4 value = 0;
 value |= (u4)(u1) values_[index - 1];

 value |= ( ((u4)(u1)values_[index]) << 8); 

 value |= ( ((u4)(u1)values_[index + 1]) << 16); 
 value |= ( ((u4)(u1)values_[index + 2]) << 32); 

 qDebug() << "Value is: " << value;
}

u4 PHRA_Binary_Channel::extract_4(u2 index)
{
 return ((u4)(u1)values_[index - 1])
   | (( ((u4)(u1)values_[index]) << 8))
   | (( ((u4)(u1)values_[index + 1]) << 16))
   | (( ((u4)(u1)values_[index + 2]) << 32));
}

void PHRA_Binary_Channel::test_extract_8(u2 index)
{
 u8 value = 0;

 value |= (u8)(u1) values_[index - 1];
 value |= ( ((u8)(u1)values_[index]) << 8); 
 value |= ( ((u8)(u1)values_[index + 1]) << 16);
 value |= ( ((u8)(u1)values_[index + 2]) << 24);
 value |= ( ((u8)(u1)values_[index + 3]) << 32);
 value |= ( ((u8)(u1)values_[index + 4]) << 40); 
 value |= ( ((u8)(u1)values_[index + 5]) << 48); 
 value |= ( ((u8)(u1)values_[index + 6]) << 56);

 qDebug() << "Value is: " << value;
}

u8 PHRA_Binary_Channel::extract_8(u2 index)
{
 return ((u8)(u1)values_[index - 1])
   | (( ((u8)(u1)values_[index]) << 8))
   | (( ((u8)(u1)values_[index + 1]) << 16))
   | (( ((u8)(u1)values_[index + 2]) << 32))
   | (( ((u8)(u1)values_[index + 3]) << 32))
   | (( ((u8)(u1)values_[index + 4]) << 40)) 
   | (( ((u8)(u1)values_[index + 5]) << 48)) 
   | (( ((u8)(u1)values_[index + 6]) << 56));
}


void PHRA_Binary_Channel::set_kind(const std::string& ss)
{
 set_kind(QString::fromStdString(ss));
}

void PHRA_Binary_Channel::test_extract(u2 index, u1 length)
{
 switch(length)
 {
 case 1: test_extract_1(index); break;
 case 2: test_extract_2(index); break;
 case 4: test_extract_4(index); break;
 case 8: test_extract_8(index); break;
 default: break;
 }
}

void PHRA_Binary_Channel::append(u1 u)
{
 int sz = values_.size();
 values_.append(1, 0);
 values_[sz] = u; 
 mask_ <<= 3;
}

void PHRA_Binary_Channel::append(u2 u)
{
 int sz = values_.size();
 values_.append(2, 0);
 values_[sz] =      u & 0x00ff; 
 values_[sz + 1] = (u & 0xff00) >> 8; 
 mask_ <<= 3;
 mask_ |= 1;
}

void PHRA_Binary_Channel::append(u4 u)
{
 int sz = values_.size();

 values_.append(4, 0);
 values_[sz] =      u & 0x000000ff; 
 values_[sz + 1] = (u1) ((u & 0x0000ff00) >> 8); 
 values_[sz + 2] = (u1) ((u & 0x00ff0000) >> 16); 
 values_[sz + 3] = (u1) ((u & 0xff000000) >> 24); 

 mask_ <<= 3;
 mask_ |= 3;
}

void PHRA_Binary_Channel::append(u8 u)
{
 int sz = values_.size();
 values_.append(8, 0);
 values_[sz] =     (u1) (u & 0x00000000000000ff); 
 values_[sz + 1] = (u1) ((u & 0x000000000000ff00) >> 8); 
 values_[sz + 2] = (u1) ((u & 0x0000000000ff0000) >> 16); 
 values_[sz + 3] = (u1) ((u & 0x00000000ff000000) >> 24); 
 values_[sz + 4] = (u1) ((u & 0x000000ff00000000) >> 32); 
 values_[sz + 5] = (u1) ((u & 0x0000ff0000000000) >> 40); 
 values_[sz + 6] = (u1) ((u & 0x00ff000000000000) >> 48); 
 values_[sz + 7] = (u1) ((u & 0xff00000000000000) >> 56); 

 mask_ <<= 3;
 mask_ |= 7;
}

u8 PHRA_Binary_Channel::short_mask()
{
 u8 result = 0;
 for(u8 m = mask_; m > 0; m >>= 3)
 {
  result <<= 2;
  switch(m & 7)
  {
  case 0: break;
  case 1: result |= 1; break;
  case 3: result |= 2; break;
  case 7: result |= 3; break;
  default: break;
  }
 }
 return result;
}

u8 PHRA_Binary_Channel::mask_hint(u1 ret)
{
 u8 result = ret;
 u8 mult = 1;
 u8 temp = 0;
 for(u8 m = mask_; m > 0; m >>= 3)
 {
  result *= 10;
  switch(m & 7)
  {
  case 0: temp += mult; break;
  case 1: temp += (mult * 2); break;
  case 3: temp += (mult * 4); break;
  case 7: temp += (mult * 8); break;
  default: break;
  }
  mult *= 10; 
 }
 return result + temp;
}

void PHRA_Binary_Channel::add_ref()
{
 // Increase the reference counter
 ref_count_++;
}
 
void PHRA_Binary_Channel::release()
{
 // Decrease ref count and delete if it reaches 0
 if( --ref_count_ == 0 )
   delete this;
}


