
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef RZ_NGML_OUTPUT_LATEX__H
#define RZ_NGML_OUTPUT_LATEX__H

#include <QTextStream>


#include "rz-ngml-output-base.h"
#include "rz-ngml-output-event-handler.h"

#include "kans.h"

KANS_CLASS_DECLARE(HTXN, HTXN_Node_Detail)
USING_KANS(HTXN)

#include "rzns.h"

RZNS_(NGML)

class NGML_Graph;
class NGML_Document;

class NGML_HTXN_Node;

class NGML_Attribute_Tile;
class NGML_Tile;


class NGML_Output_Latex : public NGML_Output_Base, private NGML_Output_Event_Handler
{
 QMap<QString, caon_ptr<NGML_Command_Callback>> callbacks_;
 void init_callbacks();

 QString htxn_acc_;
 QTextStream htxn_qts_;

 QMap<HTXN_Node_Detail*, QString> region_end_names_;

public:


 NGML_Output_Latex(NGML_Document& document);

 void export_latex(QString path = "..tex");
 void write_latex_output(QString& latex_output);

 void generate(QTextStream& qts);

 void generate_tag_command_entry(const NGML_Output_Bundle& b, caon_ptr<NGML_Tag_Command> ntc) Q_DECL_OVERRIDE;

 void generate_tag_command_entry(const NGML_Output_Bundle& b, NGML_HTXN_Node& nhn);

 void generate_tag_command_leave(const NGML_Output_Bundle& b, caon_ptr<NGML_Tag_Command> ntc) Q_DECL_OVERRIDE;
 void generate_tag_command_leave(const NGML_Output_Bundle& b, NGML_HTXN_Node& nhn);

 void generate_tag_body_leave(const NGML_Output_Bundle& b, caon_ptr<NGML_Tag_Command> ntc) Q_DECL_OVERRIDE;
 void generate_tag_body_leave(const NGML_Output_Bundle& b, NGML_HTXN_Node& nhn);

 void generate_tile(const NGML_Output_Bundle& b, caon_ptr<NGML_Paralex_Tile> tile) Q_DECL_OVERRIDE;
 void generate_tile(const NGML_Output_Bundle& b, caon_ptr<NGML_Attribute_Tile> tile) Q_DECL_OVERRIDE;
 void generate_tile_via_htxn(const NGML_Output_Bundle& b, NGML_HTXN_Node& nhn) Q_DECL_OVERRIDE;

 void handle_annotation(caon_ptr<NGML_Tile> tile, caon_ptr<NGML_Annotation_Tile> atile) Q_DECL_OVERRIDE;

 caon_ptr<NGML_Command_Callback> check_command_callback(caon_ptr<NGML_Tag_Command> ntc)  Q_DECL_OVERRIDE;

 
};

_RZNS(NGML)


#endif
