
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef NTXH_PARSE_CONTEXT__H
#define NTXH_PARSE_CONTEXT__H

#include "relae-graph/relae-parser.h"

#include "flags.h"

#include "kans.h"
KANS_(HGDMCore)

//USING_RZNS(RECore)

class NTXH_Graph;
class NTXH_Node;

//flag_(1, inside_tag_body);
//flag_(2, inside_tag_command_main_argument);
//flag_(3, pre_markup);

class NTXH_Parse_Context
{
 typedef NTXH_Node tNode;

public:
 flags_(1)
  flag_(1, inside_comment)
  flag_(2, multiline_field)
  flag_(3, active_type_decl)
 _flags_

private:
//? caon_ptr<NTXH_Node> current_open_print_node_;

public:

 NTXH_Parse_Context();

};

_KANS(HGDMCore)

#endif
