
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef HTXN_NODE_DETAIL__H
#define HTXN_NODE_DETAIL__H

#include "accessors.h"

#include "flags.h"

#include "kans.h"

#include <QString>
#include <QList>
#include <QDate>

#include <functional>


KANS_(HTXN)

typedef quint8 u1;
typedef quint16 u2;
typedef quint32 u4;
typedef quint64 u8;

struct HTXN_Node_Detail
{
flags_(2)
 bool region:1;
 bool self_close:1;
 bool optional:1;
 bool key_with_ref:1;
 bool key_no_ref:1; 
 bool has_continue:1;
_flags

 void* node_ref;

 u4 enter;
 u4 leave;

// u8 get_encoding();
// u8 get_raw_encoding();

 HTXN_Node_Detail(u4 e, u4 l);

 HTXN_Node_Detail();
};

_KANS(HTXN)

#endif // HTXN_NODE_DETAIL__H