
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "ngml-htxn-node.h"

#include "htxn/htxn-document-8b.h"

USING_RZNS(NGML)

NGML_HTXN_Node::NGML_HTXN_Node(u4 detail_code) 
  :  detail_code_(detail_code), 
     layer_code_(0), range_({0,0})
{

}

HTXN_Node_Detail* NGML_HTXN_Node::get_node_detail(HTXN_Document_8b* doc)
{
 if(detail_code_ == 0)
   return nullptr;
 return doc->get_node_detail(detail_code_);
}


void NGML_HTXN_Node::set_range_enter(u4 enter)
{
 range_.first = enter;
}

void NGML_HTXN_Node::set_range_leave(u4 leave)
{
 range_.second = leave;
}


u4 NGML_HTXN_Node::get_range_enter()
{
 return range_.first;
}

u4 NGML_HTXN_Node::get_range_leave()
{
 return range_.second;
}

