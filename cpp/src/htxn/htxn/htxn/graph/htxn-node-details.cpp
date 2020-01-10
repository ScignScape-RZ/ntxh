
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "htxn-node-details.h"

#include <QTextStream>

USING_KANS(HTXN)

HTXN_Node_Details::HTXN_Node_Details()
{

}

HTXN_Node_Detail* HTXN_Node_Details::tie_detail_range(u4 nc1, u4 nc2)
{
 HTXN_Node_Detail& nd1 = node_details_[nc1 - 1];
 nd1.add_node_ref(nc2);
 return &nd1; 
}


HTXN_Node_Detail* HTXN_Node_Details::add_detail_range( // Glyph_Layer_8b* layer, 
  u4 enter, u4 leave, u4& nc)
{
 node_details_.push_back({enter, leave});
 nc = node_details_.size();
 return &(node_details_[nc - 1]);
}

KANS_(HTXN)

QTextStream& operator<<(QTextStream& qts, 
  const HTXN_Node_Detail& rhs)
{
 qts << rhs.Flags << ';' << rhs.enter << ':' << rhs.leave;
 return qts;
}

QTextStream& operator<<(QTextStream& qts, 
  const QVector<HTXN_Node_Detail>& rhs)
{
 qts << rhs.length() << "\n";
 for(const HTXN_Node_Detail& nd : rhs)
   qts << nd << "\n"; 
 return qts;
}

QTextStream& operator>>(QTextStream& qts, 
  HTXN_Node_Detail& rhs)
{
 char c;
 qts >> rhs.Flags >> c >> rhs.enter >> c >> rhs.leave;
 return qts;
}

QTextStream& operator>>(QTextStream& qts, 
  QVector<HTXN_Node_Detail>& rhs)
{
 int sz; 
 qts >> sz;
 rhs.resize(sz);
  // // read the newline
 qts.read(1);
 for(HTXN_Node_Detail& nd : rhs)
 {
  qts >> nd;
   // // read the newline
  qts.read(1);
 } 
 return qts;
}

_KANS(HTXN)


