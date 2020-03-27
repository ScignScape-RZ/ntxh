
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phra-channel-runner.h"

#include "phra-function-table.h"

#include "channels/phra-binary-channel.h"



void test(u2 x, u4 y)
{
 qDebug() << "x = " << x << ", y = " << y;
}


PHRA_Channel_Runner::PHRA_Channel_Runner(PHRA_Function_Table& pft, PHRA_Binary_Channel& pbc)
  :  pft_(pft), pbc_(pbc)
{

}

void PHRA_Channel_Runner::run(u8 mh)
{
 PHRA_Function_Table::_s0a_fn1_16_32_type fn = 
   pft_.get_fn(fname_);

 switch(mh)
 {
 case 924:{
   u2 arg1 = pbc_.extract_2(1);
   u4 arg2 = pbc_.extract_4(3);
   fn(arg1, arg2);
  }; break;
 default: break;
 }

 //u8 a0 = ( ((u8) arg1) << 16) | arg2;
 //test(2020, 19);

// char cs[6] = {10, 0, 0, 0, 0, 0};
 

// void (*fn)(u2, u4) = &test;
// void (*fn)(char[6]) = ( void(*)(char[6]) )  &test;
// fn(cs);
// fn(arg1, arg2);
 
}


