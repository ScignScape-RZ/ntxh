
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHRA_BINARY_CHANNEL__H
#define PHRA_BINARY_CHANNEL__H

#include <QDebug>
#include <QVector>
#include <QString>
#include <QByteArray>

#include "angelscript.h"

#include "rzns.h"

#include "global-types.h"

#include "accessors.h"


RZNS_CLASS_DECLARE(PhrGraphCore ,PHR_Graph)
RZNS_CLASS_DECLARE(PhrGraphCore ,PHR_Graph_PHR_Output)

RZNS_CLASS_DECLARE(PhrGraphCore ,PHR_Graph_Frame)
RZNS_CLASS_DECLARE(PhrGraphCore ,PHR_Graph_Query)

USING_RZNS(PhrGraphCore)

class PHRA_Graph_Build;

class PHRA_Binary_Channel
{
 QString kind_;
 QByteArray values_;
 u8 mask_;

 int ref_count_;
 
public:

 PHRA_Binary_Channel(); 

 ACCESSORS(QString ,kind)
 ACCESSORS(u8 ,mask)

 u8 mask_hint(u1 ret);
 u8 short_mask();

 void set_kind(const std::string& ss);

 void append(u1 u);
 void append(u2 u);
 void append(u4 u);
 void append(u8 u);

 void test_extract(u2 index, u1 length);
 void test_extract_1(u2 index);
 void test_extract_2(u2 index);
 void test_extract_4(u2 index);
 void test_extract_8(u2 index);

 u1 extract_1(u2 index);
 u2 extract_2(u2 index);
 u4 extract_4(u2 index);
 u8 extract_8(u2 index);


 void add_ref();
 void release();
};


#endif //  PHRA_BINARY_CHANNEL__H

