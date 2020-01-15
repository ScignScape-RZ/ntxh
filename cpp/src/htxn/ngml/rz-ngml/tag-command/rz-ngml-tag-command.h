
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef RZ_NGML_TAG_COMMAND__H
#define RZ_NGML_TAG_COMMAND__H

#include <QString>

#include "accessors.h"
#include "flags.h"

#include "whitespace/rz-ngml-whitespace-holder.h"

#include "global-types.h"

#include "rzns.h"

RZNS_(NGML)

class NGML_Tag_Command : public NGML_Whitespace_Holder
{
public:

 flags_(2)
  bool is_environment:1;
  bool is_closed:1;
  bool is_html:1;
  bool is_auto_closed:1;
  bool is_tag_assertion:1;
  bool is_tag_query:1;
  bool is_understood_auto_closed:1;
  bool has_main_tile:1;
  bool has_entry:1;
  bool has_attribute_tile:1;
 _flags

public:

 QString name_;
 QString argument_; 

 QString parent_tag_type_;

 u4 ref_position_;
 u4 ref_order_;

public:

 ACCESSORS(QString ,name)
 ACCESSORS(QString ,parent_tag_type)
 ACCESSORS(QString ,argument)

 ACCESSORS(u4 ,ref_position)
 ACCESSORS(u4 ,ref_order)

 NGML_Tag_Command(QString name, QString argument,
   QString parent_tag_type = QString());

 QString latex_name();

};

_RZNS(NGML)

#endif
