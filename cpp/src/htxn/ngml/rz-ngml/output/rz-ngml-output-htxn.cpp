
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "rz-ngml-output-htxn.h"

#include "rz-ngml-output-event-generator.h"
#include "kernel/document/rz-ngml-document.h"
#include "kernel/output/rz-ngml-output-bundle.h"
#include "tile/rz-ngml-token.h"
#include "tile/rz-ngml-tile.h"
#include "kernel/graph/rz-ngml-node.h"
#include "tag-command/rz-ngml-tag-command.h"
#include "kernel/rz-ngml-root.h"
#include "tag-command/rz-ngml-command-callback.h"

#include "tile/rz-ngml-paralex-tile.h"

#include "htxn/glyph-layer-8b.h"

#include <QFile>
#include <QFileInfo>
#include <QDebug>

#include "rzns.h"

USING_RZNS(NGML)


NGML_Output_HTXN::NGML_Output_HTXN(NGML_Document& document)
 : NGML_Output_Base(document), NGML_Output_Event_Handler(),
   current_multi_arg_(nullptr), tag_command_arg_index_(2)
{
 init_callbacks();

 htxn_document_.add_standard_deck();
 htxn_document_.add_standard_diacritic_deck();
// Glyph_Layer_8b* 

 main_gl_ = htxn_document_.add_layer();
 tag_command_gl_ = htxn_document_.add_layer();
 tag_command_arg_gl_ = htxn_document_.add_layer();

 tag_command_arg_qts_.setString(&tag_command_arg_layer_);
}

void NGML_Output_HTXN::init_callbacks()
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

 #include "rz-ngml-output-htxn.callbacks.h"

}

void NGML_Output_HTXN::write_htxne_output(QString& htxne_output)
{
 QTextStream qts(&htxne_output);
 generate(qts);
// htxne_output.replace("$OP$", "(");
// htxne_output.replace("$CP$", ")");
// htxne_output.replace("$EQ$", "=");
}

void NGML_Output_HTXN::generate(QTextStream& qts)
{
 NGML_Output_Event_Generator events(*this, *this);
 events.generate(qts);
}

void NGML_Output_HTXN::generate_root(const NGML_Output_Bundle& b, caon_ptr<NGML_Root> nr)
{
 htxne_top_ += "## htxne generated...\n";
 QStringList lines = nr->ws().to_string().split('\n');
 QStringListIterator it(lines);
 while(it.hasNext())
 {
  QString l = it.next();
  if( (!it.hasNext()) && l.isEmpty())
    break;
  htxne_top_ += QString("# %1 \n").arg(l);
 }
}

void NGML_Output_HTXN::write_latex_out(QString path)
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
 
 QFile file(path);
 if(file.open(QIODevice::WriteOnly | QIODevice::Text))
 {
  QTextStream qts(&file);
  qts << htxne_top_;
  htxn_document_.write_latex_out(qts); 
 }
}


void NGML_Output_HTXN::export_htxne(QString path)
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
 QString htxne_output;
 write_htxne_output(htxne_output);

 htxn_document_.read_layer(main_gl_, htxne_output);
 htxn_document_.read_layer(tag_command_gl_, tag_command_layer_);
 htxn_document_.read_layer(tag_command_arg_gl_, tag_command_arg_layer_);

 QFile outfile(path);
 if(outfile.open(QFile::WriteOnly | QIODevice::Text))
 {
  htxne_path_ = path;
  htxn_document_.write_htxne_out(outfile);
//  outfile.write(htxne_output.toLatin1());
  outfile.close();
 }


// QFile outfile(path);
// if(outfile.open(QFile::WriteOnly | QIODevice::Text))
// {
//  outfile.write(htxne_output.toLatin1());
//  outfile.close();
// }

}

caon_ptr<NGML_Command_Callback> NGML_Output_HTXN::check_command_callback(caon_ptr<NGML_Tag_Command> ntc)
{
 QString name = ntc->name();
 return callbacks_.value(name, caon_ptr<NGML_Command_Callback>( nullptr ));
}

void NGML_Output_HTXN::check_generate_whitespace(const NGML_Output_Bundle& b, caon_ptr<NGML_Tag_Command> ntc)
{
 //? ntc->write_whitespace(b.qts);
 //? check_update_index_after_whitespace(b, ntc);
}

void NGML_Output_HTXN::check_post_callback
 (QTextStream& qts, caon_ptr<NGML_Command_Callback> cb, caon_ptr<tNode> node)
{
 if(cb->flags.has_post_callback)
 {
  cb->post_callback(qts, node, cb);
 }
}

void NGML_Output_HTXN::generate_tag_command_auto_leave(const NGML_Output_Bundle& b, caon_ptr<NGML_Tag_Command> ntc)
{
 // b.qts << "/>";
}

u4 NGML_Output_HTXN::split_arg_layer_arguments(QString arg,
  QStringList& args)
{
 if(arg.isEmpty())
   return 0;
 QString trim = arg.trimmed();
 if(trim.isEmpty())
 {
  args = QStringList {" "};
  return 1;
 }
 QChar c = trim[0];
 if( (c != '?') && (c != '!') )
 {
  args = QStringList {arg};
  return 1;
 }
 trim.replace(" ? ", " >? ");
 trim.replace(" ! ", " >! ");
 args = trim.split('>');
 return args.size();
}

void NGML_Output_HTXN::tie_multi_optional_main_layer(const NGML_Output_Bundle& b,
  NGML_Tag_Command& ntc)
{
 u4 nc1 = multi_parent_range_stack_.top().first;
 u4 enter = 0;
 u4 leave = 0;
 u4 nc2 = htxn_document_.add_detail_range_optional(tag_command_arg_gl_, enter, leave);
 htxn_document_.tie_detail_range_preempt(nc1, nc2);
}

void NGML_Output_HTXN::tie_multi_mandatory_main_layer(const NGML_Output_Bundle& b,
  NGML_Tag_Command& ntc)
{
 u4 nc1 = multi_parent_range_stack_.top().first;
 u4 enter = 0;
 u4 leave = 0;
 u4 nc2 = htxn_document_.add_detail_range_optional(tag_command_arg_gl_, enter, leave);
 htxn_document_.tie_detail_range_preempt(nc1, nc2);
}

void NGML_Output_HTXN::tie_multi_optional_arg_layer(const NGML_Output_Bundle& b,
  NGML_Tag_Command& ntc)
{
 u4 nc1 = multi_parent_range_stack_.top().first;
 u4 enter = 0;
 u4 leave = 0;
 u4 nc2 = htxn_document_.add_detail_range_optional(tag_command_arg_gl_, enter, leave);
 htxn_document_.tie_detail_range_preempt(nc1, nc2);
}

void NGML_Output_HTXN::tie_multi_mandatory_arg_layer(const NGML_Output_Bundle& b,
  NGML_Tag_Command& ntc)
{
 u4 nc1 = multi_parent_range_stack_.top().first;
 u4 enter = 0;
 u4 leave = 0;
 u4 nc2 = htxn_document_.add_detail_range_optional(tag_command_arg_gl_, enter, leave);
 htxn_document_.tie_detail_range_preempt(nc1, nc2);
}

void NGML_Output_HTXN::generate_tag_command_entry(const NGML_Output_Bundle& b, caon_ptr<NGML_Tag_Command> ntc)
{
 CAON_PTR_B_DEBUG(NGML_Node ,node)
 chiefs_.push(b.node);

 CAON_PTR_DEBUG(NGML_Tag_Command ,ntc)

 switch(b.connection_descriptor)
 {
 case NGML_Connection_Descriptor::Tag_Command_Cross:
  //?
 case NGML_Connection_Descriptor::Tag_Command_Entry:

  caon_ptr<NGML_Command_Callback> cb = b.cb;

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

  if( (ntc->flags.is_multi_optional) || (ntc->flags.is_multi_mandatory) )
  {
   current_multi_arg_ = ntc;
   multi_parent_range_stack_.top().second.push_back(ntc);
//   u4 nc1 = multi_parent_range_stack_.top();
//   if(ntc->flags.multi_arg_layer)
//     tie_multi_optional_arg_layer(b, nc1, *ntc);
//   else if(ntc->flags.multi_main_layer)
//     tie_multi_optional_main_layer(b, nc1, *ntc);
   return;
  }

  QString command_print_name;
  if(cb && cb->flags.has_rename)
    command_print_name = cb->rename_tag();
  else
    command_print_name = ntc->name();

  QString style_class_name;
  if(cb && cb->flags.has_rename_style_class)
   style_class_name = cb->rename_style_class();

  //u4 pos = (u4) b.qts.pos();

  u4 span_start, span_end;

  auto it = tag_command_spans_.find(command_print_name);
  if(it == tag_command_spans_.end())
  {
   span_start = tag_command_layer_.size() + 2;
   span_end = span_start + command_print_name.size() - 1;

   tag_command_spans_.insert(command_print_name,
     {span_start, span_end});
   tag_command_layer_ += command_print_name;
  }
  else
  {
   span_start = (*it).first;
   span_end = (*it).second;
  }

  u4 nc1;

  if(ntc->flags.is_region)
    nc1 = htxn_document_.add_detail_range_region(tag_command_gl_, span_start, span_end);
  else
    nc1 = htxn_document_.add_detail_range(tag_command_gl_, span_start, span_end);

  if(ntc->flags.is_multi_parent)
    multi_parent_range_stack_.push({nc1, {}});

  QStringList args;
  u4 sz = split_arg_layer_arguments(ntc->argument(), args);
  if(sz > 0)
  {
   if(sz == 1)
   {
    u4 enter = tag_command_arg_index_;// tag_command_arg_layer_.size() + 2;
    tag_command_arg_qts_ << args[0]; //tag_command_arg_layer_ += args[0];
    tag_command_arg_index_ += args[0].size(); //qts_
    u4 leave = tag_command_arg_index_;
    u4 nc2 = htxn_document_.add_detail_range(tag_command_arg_gl_, enter, leave);
    htxn_document_.tie_detail_range_preempt(nc1, nc2);
   }
   else for(QString arg : args)
   {
    QChar c = arg[0];
    QString a = arg.mid(1).trimmed();
    u4 enter = tag_command_arg_index_; //tag_command_arg_layer_.size() + 2;
    tag_command_arg_qts_ << a;
    tag_command_arg_index_ += a.size();
    u4 leave = tag_command_arg_index_;
    u4 nc2;
    if(c == '?')
      nc2 = htxn_document_.add_detail_range_optional(tag_command_arg_gl_, enter, leave);
    else if(c == '!')
      nc2 = htxn_document_.add_detail_range(tag_command_arg_gl_, enter, leave);
    htxn_document_.tie_detail_range_preempt(nc1, nc2);
   }
   //tag_command_gl_->
  }

  //ntc->set_detail_code(nc1);
  u4 order = main_gl_->add_range(b.index, 0, nc1);
  ntc->set_ref_position(b.index);
  ntc->set_ref_order(order);
//  b.qts << '\n' << '[' << command_print_name;

//?  if(!style_class_name.isEmpty())
//?   b.qts << " class='" << style_class_name << '\'';

  break;
 }
}

void NGML_Output_HTXN::generate_tag_command_leave(const NGML_Output_Bundle& b,
 caon_ptr<NGML_Tag_Command> ntc)
{
 if(b.cb)
 {
  if(b.cb->flags.has_post_callback)
  {
   b.cb->post_callback(b.qts, b.node, b.cb);
  }
  if(!b.cb->flags.post_fallthrough)
   return;
 }

 CAON_PTR_DEBUG(NGML_Tag_Command ,ntc)

 QString command_print_name;
 if(b.cb && b.cb->flags.has_rename)
  command_print_name = b.cb->rename_tag();
 else
  command_print_name = ntc->name();

 if(ntc->flags.is_multi_parent)
   multi_parent_range_stack_.pop();

 if(ntc->flags.is_multi_optional)
 {
  if(ntc->flags.multi_arg_layer)
    tie_multi_mandatory_arg_layer(b, *ntc);
  else if(ntc->flags.multi_main_layer)
    tie_multi_mandatory_main_layer(b, *ntc);
 }
 else if(ntc->flags.is_multi_mandatory)
 {
  if(ntc->flags.multi_arg_layer)
    tie_multi_mandatory_arg_layer(b, *ntc);
  else if(ntc->flags.multi_main_layer)
    tie_multi_mandatory_main_layer(b, *ntc);
 }
 else if(!ntc->flags.is_self_closed)
   main_gl_->set_range_leave(ntc->ref_position(), ntc->ref_order(), b.index);


 //? range_starts_[write_position_] = {span_start, span_end};

//? b.qts << "</" << ntc->name() << '>';
}

void NGML_Output_HTXN::generate_tile(const NGML_Output_Bundle& b, caon_ptr<NGML_Paralex_Tile> tile)
{
 if(current_multi_arg_)
 {
  if(current_multi_arg_->flags.multi_arg_layer)
  {
  //    || (current_multi_arg_->flags.is_multi_mandatory) )
   tag_command_arg_qts_ << tile->to_string();
   tag_command_arg_index_ += tile->get_width();
   return;
  }
 }

 b.qts << tile->to_string();
 b.index += tile->get_width();
// tile->write_html(b.qts);
// check_generate_whitespace(b, tile);
}

void NGML_Output_HTXN::generate_tag_body_leave(const NGML_Output_Bundle& b, caon_ptr<NGML_Tag_Command> ntc)
{
//? b.qts << '>';
//? ntc->write_whitespace(b.qts);
}


