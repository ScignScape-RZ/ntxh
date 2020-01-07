
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "htxn-node-details.h"

USING_KANS(HTXN)

HTXN_Node_Details::HTXN_Node_Details()
{

}

HTXN_Node_Detail* HTXN_Node_Details::add_detail_range( // Glyph_Layer_8b* layer, 
  u4 enter, u4 leave, u4& nc)
{
 node_details_.push_back({enter, leave});
 nc = node_details_.size();
 return &(node_details_[nc - 1]);
}


