
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "rz-ngml-output-latex.h"

#include "rz-ngml-output-event-generator.h"
#include "kernel/document/rz-ngml-document.h"
#include "kernel/output/rz-ngml-output-bundle.h"
#include "tag-command/rz-ngml-tag-command.h"
#include "tile/rz-ngml-paralex-tile.h"

#include "tag-command/rz-ngml-command-callback.h"

#include "kernel/graph/rz-ngml-node.h"

#include "ngml-htxn/ngml-htxn-node.h"


#include "htxn/htxn-document-8b.h"


#include <QFile>
#include <QFileInfo>
#include <QRegularExpression>

#include "rzns.h"
USING_RZNS(NGML)


NGML_Output_Latex::NGML_Output_Latex(NGML_Document& document)
 : NGML_Output_Base(document)
{
 htxn_qts_.setString(&htxn_acc_);
 init_callbacks();
}

void NGML_Output_Latex::init_callbacks()
{
#define RENAME_(name, tag, style_class) \
 callbacks_[#name] = caon_ptr<NGML_Command_Callback>( new NGML_Command_Callback(#name, #tag, #style_class) ); \


#define RENAME_TAG(name, tag) \
 callbacks_[#name] = caon_ptr<NGML_Command_Callback>( new NGML_Command_Callback(#name, #tag) ); \


#define NGML_CALLBACK_(name) \
 callbacks_[#name] = caon_ptr<NGML_Command_Callback>( new NGML_Command_Callback(#name, \
  NGML_Command_Callback::Callback_Map_type{{ \

#define WHEN_(kind) \
 {#kind, [this](QTextStream& qts, caon_ptr<tNode> node, caon_ptr<NGML_Command_Callback> cb)

#define _WHEN },

#define _WHEN_(kind) _WHEN WHEN_(kind)

#define _NGML_CALLBACK }}) );

 #include "rz-ngml-output-latex.callbacks.h"

}

void NGML_Output_Latex::generate_tile(const NGML_Output_Bundle& b, caon_ptr<NGML_Attribute_Tile> tile)
{
}


void NGML_Output_Latex::write_latex_output(QString& latex_output)
{
 QTextStream qts(&latex_output);
 generate(qts);
 latex_output.replace(QRegularExpression("\\n{2,}"), "\n\n");
}

void NGML_Output_Latex::generate(QTextStream& qts)
{
 NGML_Output_Event_Generator events(*this, *this);
 events.generate(qts);
}

void NGML_Output_Latex::export_latex(QString path)
{
 if(path.startsWith(".."))
 {
  path.remove(0, 1);
  path.prepend(document_.local_path());
 }
 else if(path.startsWith('.'))
 {
  QFileInfo qfi(document_.local_path());
  path.prepend(qfi.absolutePath() + '/' + qfi.completeBaseName());
 }
 QString latex_output;
 write_latex_output(latex_output);

 // //temp
 latex_output.replace("@@", "%%");
 latex_output.replace("#{", "\\scaps{");
 latex_output.replace("}#", "}");

 QFile outfile(path);
 if(outfile.open(QFile::WriteOnly | QIODevice::Text))
 {
  outfile.write(latex_output.toLatin1());
  outfile.close();
 }
}

void NGML_Output_Latex::handle_annotation(caon_ptr<NGML_Tile> tile, caon_ptr<NGML_Annotation_Tile> atile)
{
 document_.tag_command_annotation(tile, atile);
}


void NGML_Output_Latex::generate_tile(const NGML_Output_Bundle& b, caon_ptr<NGML_Paralex_Tile> tile)
{
 tile->write_latex(b.qts);
 check_generate_whitespace(b, tile);
}

void NGML_Output_Latex::generate_tag_command_entry(const NGML_Output_Bundle& b, NGML_HTXN_Node& nhn)
{
 HTXN_Node_Detail* nd = nhn.get_node_detail(htxn_document_);
 Glyph_Layer_8b* gl = nd->get_layer();

 if(nd->flags.pre_line_double_gap)
   b.qts << "\n\n";
 else if(nd->flags.pre_line_gap)
   b.qts << '\n';
 else if(nd->flags.pre_space_gap)
   b.qts << ' ';

 if(nd->flags.is_ghosted)
 {
  if(nd->flags.region_main_preempts_wrap)
    ; // nothing
  else if(nd->flags.optional)
    b.qts << '[';
  else
    b.qts << '{';
 }
 else
 {
  htxn_document_->write_minimal_latex_out(gl, nd->enter,
    nd->leave, htxn_qts_);

//  if(nd->flags.ref_preempts_wrap)
//    b.qts << '\\' << htxn_acc_;
  if(nd->flags.region)
  {
   b.qts << "\\begin{" << htxn_acc_;// << '}';
   region_end_names_[nd] = htxn_acc_;
  }
  else if(nd->flags.wmi_left)
  {
   if(nd->flags.wmi_with_space)
     b.qts << "{\\" << htxn_acc_ << ' ';
   else
     b.qts << "{\\" << htxn_acc_;
  }
  else
    b.qts << '\\' << htxn_acc_;// << '{';
  htxn_acc_.clear();
  htxn_qts_.reset();
 }
}

void NGML_Output_Latex::generate_tile_via_htxn(const NGML_Output_Bundle& b, NGML_HTXN_Node& nhn)
{
 htxn_document_->write_minimal_latex_out(nhn.layer_code(), nhn.range(), b.qts);
}

void NGML_Output_Latex::generate_tag_command_argument(const NGML_Output_Bundle& b,
  NGML_HTXN_Node& nhn)
{
 HTXN_Node_Detail* nd = nhn.get_node_detail(htxn_document_);
 b.qts << '{';
 htxn_document_->write_minimal_latex_out(nd->get_layer(), nd->enter, nd->leave, b.qts);
 b.qts << '}';
}

void NGML_Output_Latex::check_generate_tag_command_argument(const NGML_Output_Bundle& b,
  NGML_Tag_Command& ntc)
{
 if(NGML_HTXN_Node* nhn = ntc.arg_ngml_htxn_node())
   generate_tag_command_argument(b, *nhn);
}

void NGML_Output_Latex::generate_tag_command_entry(const NGML_Output_Bundle& b, caon_ptr<NGML_Tag_Command> ntc)
{
 CAON_PTR_B_DEBUG(NGML_Node ,node)
 CAON_PTR_DEBUG(NGML_Tag_Command ,ntc)

 caon_ptr<NGML_Command_Callback> cb = b.cb;


 switch(b.connection_descriptor)
 {
 case NGML_Connection_Descriptor::Tag_Command_Cross:
 case NGML_Connection_Descriptor::Tag_Command_Entry:
  if(cb)
  {
   CAON_PTR_DEBUG(NGML_Command_Callback ,cb)

   if(cb->flags.has_around_callback)
   {
    cb->around_callback(b.qts, b.node, b.cb);
    break;
   }

   if(cb->flags.has_pre_callback)
    cb->pre_callback(b.qts, b.node, b.cb);
   if(!cb->flags.pre_fallthrough)
    break;
  }

  if(htxn_document_)
  {
   if(NGML_HTXN_Node* nhn = ntc->ngml_htxn_node())
   {
    generate_tag_command_entry(b, *nhn);
    check_generate_tag_command_argument(b, *ntc);
    break;
   }
  }

  if(ntc->flags.is_region)
    b.qts << "\\begin{" << ntc->latex_name();
  else
    b.qts << '\\' << ntc->latex_name();
  break;
 }

 if(caon_ptr<tNode> n = qry_.Tag_Command_Annotation(b.node))
 {
  if(caon_ptr<tNode> mt = qry_.Tag_Command_Main_Tile(b.node))
  {
   if(caon_ptr<NGML_Tile> nt = mt->ngml_tile())
    tag_command_annotation(nt, n);
  }
 }
}

void NGML_Output_Latex::generate_tag_command_leave(const NGML_Output_Bundle& b, NGML_HTXN_Node& nhn)
{
 HTXN_Node_Detail* nd = nhn.get_node_detail(htxn_document_);

 if(nd->flags.is_ghosted)
 {
  if(nd->flags.region_main_preempts_wrap)
    ; // nothing ...
  else if(nd->flags.optional)
    b.qts << ']';
  else
    b.qts << '}';
 }
 else if(nd->flags.ref_preempts_wrap)
 {
  if(nd->flags.region)
  {
    // // should be some sort of whitespace flag ...
   b.qts << "%\n";
   b.qts << "\\end{" << region_end_names_.take(nd) << '}';
  }
 }
 else if(nd->flags.region)
   b.qts << "\\end{" << region_end_names_.take(nd) << '}';
 else if(nd->flags.wmi_none)
   ; // nothing
 else
   b.qts << '}';

 if(nd->flags.post_line_double_gap)
   b.qts << "\n\n";
 else if(nd->flags.post_line_gap)
   b.qts << '\n';
 else if(nd->flags.post_space_gap)
   b.qts << ' ';
}


void NGML_Output_Latex::generate_tag_command_leave(const NGML_Output_Bundle& b, caon_ptr<NGML_Tag_Command> ntc)
{
 CAON_PTR_DEBUG(NGML_Tag_Command ,ntc)

 if(b.cb)
 {
  if(b.cb->flags.has_post_callback)
  {
   b.cb->post_callback(b.qts, b.node, b.cb);
  }
  if(!b.cb->flags.post_fallthrough)
   return;
 }

 if(htxn_document_)
 {
  if(NGML_HTXN_Node* nhn = ntc->ngml_htxn_node())
  {
   generate_tag_command_leave(b, *nhn);
   return;
  }
 }

 if(ntc->flags.is_region)
   b.qts << "\\end{" << ntc->latex_name() << '}';
 else
   b.qts << '}';
}

void NGML_Output_Latex::check_generate_whitespace(const NGML_Output_Bundle& b, caon_ptr<NGML_Tile> tile)
{
 NGML_Output_Event_Handler::check_generate_whitespace(b, tile);
}

void NGML_Output_Latex::check_generate_whitespace(const NGML_Output_Bundle& b, caon_ptr<NGML_Paralex_Tile> tile)
{
 NGML_Output_Event_Handler::check_generate_whitespace(b, tile);
}

void NGML_Output_Latex::check_generate_whitespace(const NGML_Output_Bundle& b, NGML_HTXN_Node& nhn)
{
 HTXN_Node_Detail* nd = nhn.get_node_detail(htxn_document_);
 if(!nd)
   return;
 if(nd->flags.wmi_none)
   return;
  // // or take ws from the node detail?
 nhn.write_whitespace(b.qts);
}

void NGML_Output_Latex::check_generate_whitespace(const NGML_Output_Bundle& b, caon_ptr<NGML_Tag_Command> ntc)
{
 CAON_PTR_DEBUG(NGML_Tag_Command ,ntc)
 if(htxn_document_)
 {
  if(NGML_HTXN_Node* nhn = ntc->ngml_htxn_node())
  {
   check_generate_whitespace(b, *nhn);
   return;
  }
 }
 NGML_Output_Event_Handler::check_generate_whitespace(b, ntc);
 //ntc->write_whitespace(b.qts);
}

void NGML_Output_Latex::generate_tag_body_leave(const NGML_Output_Bundle& b, NGML_HTXN_Node& nhn)
{
 HTXN_Node_Detail* nd = nhn.get_node_detail(htxn_document_);

 if(nd->flags.is_ghosted)
   ; // nothing
 else if(nd->flags.wmi_left)
   ; // nothing
 else if(nd->flags.wmi_none)
 {
   ; // nothing
 }
 else if(nd->flags.ref_preempts_wrap)
 {
  if(nd->flags.region)
     b.qts << '}';
 }
 else if(nd->flags.region)
   b.qts << '}';
 else
   b.qts << '{';
}

void NGML_Output_Latex::generate_tag_body_leave(const NGML_Output_Bundle& b, caon_ptr<NGML_Tag_Command> ntc)
{
 CAON_PTR_DEBUG(NGML_Tag_Command ,ntc)

 if(htxn_document_)
 {
  if(NGML_HTXN_Node* nhn = ntc->ngml_htxn_node())
  {
   generate_tag_body_leave(b, *nhn);
   return;
  }
 }

 if(ntc->flags.is_region)
   b.qts << '}';
 else
  b.qts << '{';
}

caon_ptr<NGML_Command_Callback> NGML_Output_Latex::check_command_callback(caon_ptr<NGML_Tag_Command> ntc)
{
 QString name = ntc->name();
 return callbacks_.value(name, caon_ptr<NGML_Command_Callback> ( nullptr ));
}

