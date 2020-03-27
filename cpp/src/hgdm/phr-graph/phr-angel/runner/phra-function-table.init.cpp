
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phra-function-table.h"


void test_u2_u4(u2 x, u4 y)
{
 qDebug() << "x = " << x << ", y = " << y;
}



void init_ftable(PHRA_Function_Table*& pft)
{
 pft = new PHRA_Function_Table;
 pft->add_fn("test_u2_u4", &test_u2_u4); //_s0a_fn1_16_32_type 
}



