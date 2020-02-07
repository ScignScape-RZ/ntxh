
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef NGML_HTXN_NODE__H
#define NGML_HTXN_NODE__H 

#include "global-types.h"

#include "accessors.h"

//#define PASTE_ARG(...) __VA_ARGS__

#include "kans.h"
KANS_CLASS_DECLARE(HTXN ,HTXN_Node_Detail)
KANS_CLASS_DECLARE(HTXN ,HTXN_Document_8b)
USING_KANS(HTXN)


#include "rzns.h"

RZNS_(NGML)

class NGML_HTXN_Node 
{
 u4 detail_code_;

 u4 layer_code_;

 QPair<u4, u4> range_;

public:

 NGML_HTXN_Node(u4 detail_code = 0);

 ACCESSORS(u4 ,detail_code)
 ACCESSORS(u4 ,layer_code)

 ACCESSORS(MACRO_PASTE(QPair<u4, u4>) ,range)


 HTXN_Node_Detail* get_node_detail(HTXN_Document_8b* doc);

 u4 get_range_enter();
 u4 get_range_leave();

 void set_range_enter(u4 enter);
 void set_range_leave(u4 leave);

};

_RZNS(NGML)


#endif //  NGML_HTXN_NODE__H

