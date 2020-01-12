
#ifndef RZ_NGML_OUTPUT_HTXN__H
#define RZ_NGML_OUTPUT_HTXN__H

#include <QStack>

#include "rz-ngml-output-base.h"
#include "rz-ngml-output-event-handler.h"

#include "htxn/graph/htxn-node-detail.h"
#include "htxn/htxn-document-8b.h"

#include "global-types.h"

#include "rzns.h"

KANS_CLASS_DECLARE(HTXN ,Glyph_Layer_8b)

USING_KANS(HTXN)

RZNS_(NGML)

class NGML_Graph;
class NGML_Document;
class NGML_Command_Callback;

class NGML_Output_HTXN : public NGML_Output_Base, private NGML_Output_Event_Handler
{
 QStack<caon_ptr<NGML_Node>> chiefs_;


 QMap<QString, caon_ptr<NGML_Command_Callback>> callbacks_;
 void init_callbacks();

 void check_post_callback(QTextStream& qts,
  caon_ptr<NGML_Command_Callback> cb, caon_ptr<tNode> node);

 caon_ptr<NGML_Command_Callback> check_command_callback(caon_ptr<NGML_Tag_Command> ntc) Q_DECL_OVERRIDE;

 QString tag_command_layer_;
 QString tag_command_arg_layer_;

 Glyph_Layer_8b* tag_command_gl_;
 Glyph_Layer_8b* tag_command_arg_gl_;
 Glyph_Layer_8b* main_gl_;

 QMap<QString, QPair<u4, u4>> tag_command_spans_;

 QMap<u4, QPair<u4, u4>> range_starts_;

 u4 write_position_;

 HTXN_Document_8b htxn_document_;

public:

 NGML_Output_HTXN(NGML_Document& document);

 void export_htxne(QString path = "..htxne");
 void write_htxne_output(QString& html_output);

 void generate(QTextStream& qts);

 void generate_root(const NGML_Output_Bundle& b, caon_ptr<NGML_Root> nr) Q_DECL_OVERRIDE;

// void generate_space_following_token(const NGML_Output_Bundle& b) Q_DECL_OVERRIDE;
// void generate_token(const NGML_Output_Bundle& b, caon_ptr<NGML_Token> token) Q_DECL_OVERRIDE;
// void generate_token_connection_descriptor(const NGML_Output_Bundle& b) Q_DECL_OVERRIDE;

 void generate_tag_command_entry(const NGML_Output_Bundle& b, caon_ptr<NGML_Tag_Command> ntc) Q_DECL_OVERRIDE;

 void generate_tag_command_leave(const NGML_Output_Bundle& b, caon_ptr<NGML_Tag_Command> ntc) Q_DECL_OVERRIDE;

 void generate_tag_body_leave(const NGML_Output_Bundle& b, caon_ptr<NGML_Tag_Command> ntc) Q_DECL_OVERRIDE;

 void generate_tag_command_auto_leave(const NGML_Output_Bundle& b, caon_ptr<NGML_Tag_Command> ntc) Q_DECL_OVERRIDE;

};

_RZNS(NGML)


#endif // RZ_NGML_OUTPUT_HTXN__H


