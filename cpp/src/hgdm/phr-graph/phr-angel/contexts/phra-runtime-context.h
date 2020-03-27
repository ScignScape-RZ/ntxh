
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHRA_RUNTIME_CONTEXT__H
#define PHRA_RUNTIME_CONTEXT__H

#include <QDebug>
#include <QVector>
#include <QString>

#include "angelscript.h"

#include "rzns.h"
#include "flags.h"

#include "global-types.h"


class PHRA_Symbol_Context;
class PHRA_Value_Context;
class PHRA_Channel_Package;
class PHRA_Binary_Channel;

class PHRA_Function_Table;

class PHRA_Runtime_Context
{
 PHRA_Value_Context* values_;
 PHRA_Symbol_Context* symbols_;

 PHRA_Function_Table* ftable_;

 static PHRA_Function_Table* get_ftable();

 int ref_count_;
 
public:

 PHRA_Runtime_Context(); 

 PHRA_Value_Context* init_value_context();
 PHRA_Symbol_Context* init_symbol_context();
 PHRA_Channel_Package* new_channel_package();

 void run(PHRA_Channel_Package* pcp, 
   PHRA_Binary_Channel* pbc);

 void add_ref();
 void release();
};


#endif //  PHRA_RUNTIME_CONTEXT__H

