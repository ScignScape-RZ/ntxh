
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phra-function-table.h"


PHRA_Function_Table::PHRA_Function_Table()
{

}

void PHRA_Function_Table::add_fn(QString name, _s0a_fn1_16_32_type val)
{
 fns_[name] = val;
}

PHRA_Function_Table::_s0a_fn1_16_32_type PHRA_Function_Table::get_fn(QString name)
{
 return fns_.value(name);
}


