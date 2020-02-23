
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef RZ_NGML_OUTPUT_INFOSET__H
#define RZ_NGML_OUTPUT_INFOSET__H

#include <QStack>
#include <QTextStream>

#include "rz-ngml-output-base.h"
#include "rz-ngml-output-event-handler.h"

#include "htxn/infoset/htxn-infoset-8b.h"

#include "global-types.h"

#include "kans.h"

//?KANS_CLASS_DECLARE(HTXN, HTXN_Node_Detail)
USING_KANS(HTXN)

#include "rzns.h"


RZNS_(NGML)

class NGML_Graph;
class NGML_Document;
class NGML_Command_Callback;

class NGML_HTXN_Node;
class NGML_Output_HTXN;

class NGML_Output_Infoset : public NGML_Output_Base, private NGML_Output_Event_Handler
{
 HTXN_Infoset_8b* infoset_;

 QStack<caon_ptr<NGML_Node>> chiefs_;

 caon_ptr<tNode> suppress_node_;

 QMap<QString, caon_ptr<NGML_Command_Callback>> callbacks_;
 void init_callbacks();

 void check_post_callback(QTextStream& qts,
  caon_ptr<NGML_Command_Callback> cb, caon_ptr<tNode> node, u4 index);

 caon_ptr<NGML_Command_Callback> check_command_callback(caon_ptr<NGML_Tag_Command> ntc) Q_DECL_OVERRIDE;


public:

 NGML_Output_Infoset(NGML_Document& document, HTXN_Infoset_8b* infoset);

 void write_infoset_output(QString& output);
 void export_infoset(QString path);

//? ACCESSORS(NGML_Output_HTXN* ,ngml_output_htxn)

 void generate(QTextStream& qts);

 void generate_root(const NGML_Output_Bundle& b, caon_ptr<NGML_Root> nr) Q_DECL_OVERRIDE;

 void generate_tag_command_entry(const NGML_Output_Bundle& b, caon_ptr<NGML_Tag_Command> ntc) Q_DECL_OVERRIDE;
 void generate_tag_command_entry(const NGML_Output_Bundle& b, NGML_HTXN_Node& nhn);

 void generate_tag_command_argument(const NGML_Output_Bundle& b,
   NGML_HTXN_Node& nhn);
 void check_generate_tag_command_argument(const NGML_Output_Bundle& b,
   NGML_Tag_Command& ntc);

 void generate_tag_command_leave(const NGML_Output_Bundle& b, caon_ptr<NGML_Tag_Command> ntc) Q_DECL_OVERRIDE;
 void generate_tag_command_leave(const NGML_Output_Bundle& b, NGML_HTXN_Node& nhn);

 void generate_tag_body_leave(const NGML_Output_Bundle& b, caon_ptr<NGML_Tag_Command> ntc) Q_DECL_OVERRIDE;
 void generate_tag_body_leave(const NGML_Output_Bundle& b, NGML_HTXN_Node& nhn);

 void generate_tag_command_auto_leave(const NGML_Output_Bundle& b, caon_ptr<NGML_Tag_Command> ntc) Q_DECL_OVERRIDE;

 void generate_tile_via_htxn(const NGML_Output_Bundle& b, NGML_HTXN_Node& nhn) Q_DECL_OVERRIDE;

};

_RZNS(NGML)


#endif // RZ_NGML_OUTPUT_INFOSET__H
