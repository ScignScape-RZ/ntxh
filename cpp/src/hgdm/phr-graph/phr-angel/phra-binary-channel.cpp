
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phra-binary-channel.h"


PHRA_Binary_Channel::PHRA_Binary_Channel()
  :  ref_count_(0)
{
}

void PHRA_Binary_Channel::test_extract_1(u2 index)
{
 u1 value = (u1)values_[index - 1];
 qDebug() << "Value is: " << value;

}

void PHRA_Binary_Channel::test_extract_2(u2 index)
{
 u2 value = 0;
 value |= (u8)(u1)values_[index - 1];
 value |= ( ((u8)(u1)values_[index]) << 8); 

 qDebug() << "Value is: " << value;
}


void PHRA_Binary_Channel::test_extract_4(u2 index)
{
 u4 value = 0;
 value |= (u8)(u1) values_[index - 1];

 value |= ( ((u8)(u1)values_[index]) << 8); 

 value |= ( ((u8)(u1)values_[index + 1]) << 16); 
 value |= ( ((u8)(u1)values_[index + 2]) << 32); 

 qDebug() << "Value is: " << value;
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
}

void PHRA_Binary_Channel::append(u2 u)
{
 int sz = values_.size();
 values_.append(2, 0);
 values_[sz] =      u & 0x00ff; 
 values_[sz + 1] = (u & 0xff00) >> 8; 
}

void PHRA_Binary_Channel::append(u4 u)
{
 int sz = values_.size();

 values_.append(4, 0);
 values_[sz] =      u & 0x000000ff; 
 values_[sz + 1] = (u1) ((u & 0x0000ff00) >> 8); 
 values_[sz + 2] = (u1) ((u & 0x00ff0000) >> 16); 
 values_[sz + 3] = (u1) ((u & 0xff000000) >> 24); 
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


