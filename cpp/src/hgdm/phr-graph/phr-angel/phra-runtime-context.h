
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

RZNS_CLASS_DECLARE(PhrGraphCore ,PHR_Graph)
RZNS_CLASS_DECLARE(PhrGraphCore ,PHR_Graph_PHR_Output)

RZNS_CLASS_DECLARE(PhrGraphCore ,PHR_Graph_Frame)
RZNS_CLASS_DECLARE(PhrGraphCore ,PHR_Graph_Query)

USING_RZNS(PhrGraphCore)

class PHRA_Binary_Channel;

class PHRA_Value_Context
{
 QVector<u1> u1s_;
 QVector<u2> u2s_;

 QVector<u4> u4s_;
 QVector<u8> u8s_;

 QVector<QString> strs_;

 int ref_count_;
 
public:

 PHRA_Value_Context(); 

 void merge_binary_channel(PHRA_Binary_Channel* pbc, 
   u1 length, u8 mask); 

 void add_ref();
 void release();
};

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




class PHRA_Runtime_Context
{
 PHRA_Value_Context* values_;
 PHRA_Symbol_Context* symbols_;

 int ref_count_;
 
public:

 PHRA_Runtime_Context(); 

 PHRA_Value_Context* init_value_context();
 PHRA_Symbol_Context* init_symbol_context();

 void add_ref();
 void release();
};


#endif //  PHRA_RUNTIME_CONTEXT__H

