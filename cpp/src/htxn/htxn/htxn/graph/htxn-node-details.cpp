
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "htxn-node-details.h"

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


