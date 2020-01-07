
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef HTXN_NODE_DETAILS__H
#define HTXN_NODE_DETAILS__H

#include "accessors.h"

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

class Glyph_Layer_8b;


class HTXN_Node_Details
{ 
 QVector<HTXN_Node_Detail> node_details_;

public:

 HTXN_Node_Details();

 ACCESSORS__RGET(QVector<HTXN_Node_Detail> ,node_details)

 HTXN_Node_Detail* add_detail_range( // Glyph_Layer_8b* layer, 
   u4 enter, u4 leave, u4& nc);

};

_KANS(HTXN)

#endif // HTXN_NODE_DETAILS__H
