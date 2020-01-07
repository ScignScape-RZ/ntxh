
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "htxn-node-detail.h"

USING_KANS(HTXN)

HTXN_Node_Detail::HTXN_Node_Detail(u4 e, u4 l)
 :  Flags(0), enter(e), leave(l), node_ref(nullptr)
{

}

u8 HTXN_Node_Detail::get_encoding()
{
// u8 result = (enter << 32) | leave ;
// if(this.region)
//   result 
}

u8 HTXN_Node_Detail::get_raw_encoding()
{
// u8 result = (u8) *this;
// return result;
}

