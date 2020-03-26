
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef PHRA_SYMBOL_CONTEXT__H
#define PHRA_SYMBOL_CONTEXT__H

#include <QDebug>
#include <QVector>
#include <QString>

#include "angelscript.h"

#include "rzns.h"
#include "flags.h"

#include "global-types.h"


class PHRA_Symbol_Info
{
 flags_(1)
  bool pre_init:1;
  bool retired_init:1;
  bool constant:1;
 _flags

 u1 locator_;
 void* typeref_;

public:
  
 PHRA_Symbol_Info() : 
   Flags(0), locator_(0), typeref_(nullptr)
 {
 }

};

class PHRA_Symbol_Context
{
 QMap<QString, PHRA_Symbol_Info> symbols_;

 int ref_count_; 

public:

 PHRA_Symbol_Context(); 

 void add_ref();
 void release();
};



#endif //  PHRA_SYMBOL_CONTEXT__H

