
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef GLYPH_LAYER_8B__H
#define GLYPH_LAYER_8B__H

#include "glyph-vector-8b.h"

#include "graph/htxn-node-detail.h"

#include "flags.h"
#include "accessors.h"

KANS_(HTXN)


typedef quint8 u1;
typedef quint16 u2;
typedef quint32 u4;
typedef quint64 u8;

class HTXN_Node_Detail;


class Glyph_Layer_8b : public Glyph_Vector_8b
{
public:
 flags_(1)
  bool main:1;
  bool latex:1;
  bool xml:1;
 _flags

private:
 QString description_;

 QMap<u4, QVector<QPair<u4, u4>>> ranges_; 
 
 QMap<u4, QVector<QPair<QString, const HTXN_Node_Detail*>>> processing_leaves_;

 u4 id_;

public:
 Glyph_Layer_8b(u4 id);

 ACCESSORS(QString ,description);
 ACCESSORS(u4 ,id)

 void add_range(u4 enter, u4 leave, u4 node_code);

 u4 get_range_by_enter(u4 enter, u4& leave, u2 count);

 QVector<QPair<QString, const HTXN_Node_Detail*>> check_leave(u4 leave);
 void add_leave(u4 leave, QString cmd, const HTXN_Node_Detail* nd);

 void write_ranges(QTextStream& qts) const;
 void read_ranges(QTextStream& qts);
};


_KANS(HTXN)

#endif // GLYPH_LAYER_8B__H


