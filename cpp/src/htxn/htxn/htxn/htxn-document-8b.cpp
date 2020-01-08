
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "htxn-document-8b.h"

#include "standard-glyphdeck-8b.h"
#include "standard-diacritic-glyphdeck.h"

#include "glyph-vector-8b.h"
#include "glyph-layer-8b.h"

#include "glyph-argument-package.h"

#include <QDebug>

USING_KANS(HTXN)


HTXN_Document_8b::HTXN_Document_8b()
  :  current_deck_(nullptr), 
     current_diacritic_deck_(nullptr), 
     current_deck_code_(0),
     current_glyph_vector_(nullptr)
{
 qDebug() << "NEW";
}

void HTXN_Document_8b::add_standard_deck()
{
 current_deck_ = new Standard_GlyphDeck_8b;
 decks_by_id_.push_back({current_deck_});
 id_by_deck_[current_deck_] = decks_by_id_.size();
}

void HTXN_Document_8b::add_standard_diacritic_deck()
{
 current_diacritic_deck_ = new Standard_Diacritic_GlyphDeck;
 generic_glyph_base ggb {.dia =
   (Diacritic_GlyphDeck_Base*) current_diacritic_deck_};
 decks_by_id_.push_back(ggb);
 dia_id_by_deck_[current_diacritic_deck_] = decks_by_id_.size();
}

// void HTXN_Document_8b::sss;

QString HTXN_Document_8b::check_latex_insert(Glyph_Layer_8b& gl,
  u4 index, Glyph_Argument_Package& cmdgap, QString& result)
{
 // //  check enters ...
 u4 leave = 0;
 u2 count = 0;
 for (;;)
 {
  u4 node_code = gl.get_range_by_enter(index, leave, count);
  if(node_code == 0)
    break;
  ++count;
  const HTXN_Node_Detail& nd = node_details_[node_code - 1];
  Glyph_Layer_8b* ngl = nd.get_layer();
    //(Glyph_Layer_8b*) nd.node_ref;
  QString cmd;
  get_latex_command(*ngl, nd.enter, nd.leave, cmdgap, cmd);
  if(nd.flags.optional)
    result.append(QString("\\%1[").arg(cmd));
  else if(nd.flags.region)
    result.append(QString("\\begin{%1}").arg(cmd));
  else
    result.append(QString("\\%1{").arg(cmd));
  cmdgap.reset();
  if(leave == 0)
  {
   if(nd.flags.optional)
     result.append("]");
   else if(nd.flags.region)
     result.append(QString("\\end{%1}").arg(cmd));
   else
     result.append("}");
  }  
  else
    gl.add_leave(leave, cmd, &nd);
 }

 QString end_result;
 // // and leaves ...
 QVector<QPair<QString, const HTXN_Node_Detail*>> prs = gl.check_leave(index);
 for(auto pr: prs)
 {
  const HTXN_Node_Detail* nd = pr.second;
  if(nd->flags.optional)
    end_result.append("]");
  else if(nd->flags.region)
    end_result.append(QString("\\end{%1}").arg(pr.first));
  else
    end_result.append(QString("}"));
 }
 return end_result;
}

void HTXN_Document_8b::get_latex_command(Glyph_Layer_8b& gl, u4 enter, u4 leave,
  Glyph_Argument_Package& gap, QString& result)
{
 for(u4 i = enter; i <= leave; ++i)
 {
  this->Glyph_Layers_8b::get_latex_command_out(gl, i, gap);
  if(gap.chr.isNull())
    result.append(gap.str);
  else
    result.append(gap.chr);
  gap.reset();
 }
}


void HTXN_Document_8b::get_latex_out(u4 layer, QString& result)
{
 Glyph_Layer_8b* gl = value(layer);
 if(!gl)
   return;
 //parse_layer(gv)
 Glyph_Argument_Package gap;
 Glyph_Argument_Package cmdgap;
 gap.internal_deck = current_deck_;
 cmdgap.internal_deck = current_deck_;
 //?gap.internal_diacritic_deck = current_diacritic_deck_;
 QString end_result;
 for(u4 i = 0; i < gl->size(); ++i)
 {
  end_result = check_latex_insert(*gl, i, cmdgap, result);
  this->Glyph_Layers_8b::get_latex_out(*gl, i, gap);
  if(gap.chr.isNull())
    result.append(gap.str);
  else
    result.append(gap.chr);
  if(!end_result.isEmpty())
  {
   result.append(end_result);
   end_result.clear();
  }
  gap.reset();
 }
}


void HTXN_Document_8b::get_qstring_out(u4 layer, QString& result)
{
 Glyph_Vector_8b* gv = value(layer);
 if(!gv)
   return;
 //parse_layer(gv)
 Glyph_Argument_Package gap;
 gap.internal_deck = current_deck_;
 //?gap.internal_diacritic_deck = current_diacritic_deck_;
 for(u4 i = 0; i < gv->size(); ++i)
 {
  Glyph_Layers_8b::get_qstring_out(*gv, i, gap);
  if(gap.chr.isNull())
    result.append(gap.str);
  else
    result.append(gap.chr);
  gap.reset();
 } 
}

void HTXN_Document_8b::get_htxne_out(u4 layer, QString& result)
{
 QByteArray qba;
 get_htxne_out(layer, qba);
 result = QString::fromLatin1(qba);
}

void HTXN_Document_8b::get_htxne_out(u4 layer, QByteArray& result)
{
 Glyph_Vector_8b* gv = value(layer);
 if(!gv)
   return;
 result.reserve(gv->size());
 Glyph_Argument_Package gap;
 gap.internal_deck = current_deck_;

 u1 run_code = 0;
 u1 run_length = 0;
 u1 tilde_check = 0;

 static auto handle_alt = [&result, &run_code, 
   &run_length, &tilde_check, &gap]
   (u1 alt, char enter, char leave)
 {
  tilde_check = 0;
  if(run_length == 0) 
  {
   result.append('`');
   result.append(enter);
   result.append(gap.chr);
   run_length = 1;
   run_code = alt;
   return;
  }
  // //  now we know there's a run on
  if(run_code == alt)
  {
   result.append(gap.chr);
   if(gap.chr == leave)
   {
    // // always break the run here
    result.append(leave);
    run_length = 0;
    run_code = 0;
   }
   else
     ++run_length;
   return;
  }
  // // now we know the prior run has to break;
  switch(run_code)
  {
  case 1: result.append(")`"); break;
  case 2: result.append("]`"); break;
  case 3: result.append("}`"); break;
  case 4: result.append(">`"); break;
  default: break;
  }
  result.append(enter);
  result.append(gap.chr);
  run_length = 1;
  run_code = alt;
 };

 for(u4 i = 0; i < gv->size(); ++i)
 {
  Glyph_Layers_8b::get_htxne_out(*gv, i, gap);

  if(gap.flags.has_alt)
  {
   if(gap.flags.alt_1)
   {
    handle_alt(1, '(', ')');
   }
   else if(gap.flags.alt_2)
   {
    handle_alt(1, '{', '}');
   }
   else if(gap.flags.alt_3)
   {
    handle_alt(3, '[', ']');
   }
   else if(gap.flags.alt_4)
   {
    handle_alt(4, '<', '>');
   }
  }
  else if(run_length > 0)
  {
   // // have to break a run ...
   switch(run_code)
   {
   case 1: result.append(')'); break;
   case 2: result.append(']'); break;
   case 3: result.append('}'); break;
   case 4: result.append('>'); break;
   default: break;
   }
   run_code = 0;
   run_length = 0;
   tilde_check = 1;
   if(gap.chr.isNull())
     result.append(gap.str);
   else
     result.append(gap.chr);
  }
  else 
  {
   if(tilde_check > 0)
   {
    if(tilde_check == 1)
    {
     if(gap.chr == '~')
       tilde_check = 2;
     else 
       tilde_check = 0;
    }
    else if(tilde_check == 2)
    {
     if(gap.chr == '(')
       result.append('~');
     tilde_check = 0;
    }  
   }
   if(gap.chr.isNull())
     result.append(gap.str);
   else
     result.append(gap.chr);
  }
  gap.reset();
 }

 if(run_length > 0)
 {
  // // have to break a run ...
  switch(run_code)
  {
  case 1: result.append(')'); break;
  case 2: result.append(']'); break;
  case 3: result.append('}'); break;
  case 4: result.append('>'); break;
  default: break;
  }
 }

}

void HTXN_Document_8b::read_glyph_point(Glyph_Argument_Package& gap, 
  u4 index, Glyph_Vector_8b& gv)
{
// gv.check_exterenal(index, *current_deck_, gap);
// if(gap.flags.

}

u4 HTXN_Document_8b::add_detail_range_region(Glyph_Layer_8b* layer, u4 enter, u4 leave)
{
 u4 result = 0;
 HTXN_Node_Detail* nd = this->HTXN_Node_Details::add_detail_range(enter, leave, result);
 nd->set_layer(layer);
 nd->flags.region = true;
 return result; 

}

u4 HTXN_Document_8b::add_detail_range(Glyph_Layer_8b* layer, u4 enter, u4 leave)
{
 u4 result = 0;
 HTXN_Node_Detail* nd = this->HTXN_Node_Details::add_detail_range(enter, leave, result);
 nd->set_layer(layer);
 return result; 
}


Glyph_Layer_8b* HTXN_Document_8b::read_layer(QString text, u2 gap)
{
 Glyph_Layer_8b* result = new Glyph_Layer_8b(size());
 push_back(result);
 current_glyph_vector_ = result;
 encode_latin1(text.toLatin1(), *result, gap);
 return result;
}

u2 HTXN_Document_8b::get_diacritic_cue_code(char cue)
{
 return (u2) current_diacritic_deck_->get_cue_code(cue);
}


u2 HTXN_Document_8b::get_diacritic_code(char cue, u1 scope)
{
 return (u2) current_diacritic_deck_->get_code(cue, scope);
}

u2 HTXN_Document_8b::get_diacritic_code_inh(u1 pos, u1 length)
{
 return (u2) 
   current_diacritic_deck_->get_diacritic_code_inh(pos, length);
}

u1 HTXN_Document_8b::get_diacritic_length_or_code(char cue, u2& code)
{
 // // non-zero return means the cue character is a length 
  //   indicator.  If the result is also non-zero 
  //   the character signals both length and cue.
 QPair<u1, u1> pr = current_diacritic_deck_->get_length(cue);
 if(pr.first > 0)
 {
  code = pr.second;
  return pr.first;
 }
 code = current_diacritic_deck_->get_code(cue, 1);
 return 0;
}

void HTXN_Document_8b::encode_latin1(const QByteArray& src, 
  Glyph_Vector_8b& target, u4 index, u4& last_index)
{
 static QMap<QPair<char, u1>, quint8> static_47 {

   { { '\n', 0 }, 127 },

   { { ' ', 0 }, 63 },

   { { '.', 0 }, 64 },
   { { '.', 1 }, Standard_GlyphDeck_8b::NpDot },
   { { '.', 2 }, Standard_GlyphDeck_8b::NsPer },

   { { '!', 0 }, 65 },
   { { '!', 1 }, Standard_GlyphDeck_8b::NpExcX },

   { { '(', 0 }, 66 },
   { { '(', 1 }, Standard_GlyphDeck_8b::NpOParX },

   { { ')', 0 }, 67 },
   { { '(', 1 }, Standard_GlyphDeck_8b::NpCParX },

   { { '-', 0 }, 68 },
   { { '-', 1 }, Standard_GlyphDeck_8b::DashSML },
   { { '-', 2 }, Standard_GlyphDeck_8b::NpMinus },
   { { '-', 3 }, Standard_GlyphDeck_8b::DashX },
   { { '-', 4 }, Standard_GlyphDeck_8b::SnDash },

   { { ',', 0 }, 69 },
   { { ',', 1 }, Standard_GlyphDeck_8b::NmComX },

   { { '\'', 0 }, 70 },
   { { '\'', 1 }, Standard_GlyphDeck_8b::SqSqX },

   { { '#', 0 }, 76 },
   { { '#', 1 }, Standard_GlyphDeck_8b::TxtNumX },

   { { '$', 0 }, 77 },
   { { '$', 1 }, Standard_GlyphDeck_8b::TxtDolX },

   { { '%', 0 }, 78 },
   { { '%', 1 }, Standard_GlyphDeck_8b::TxtPerX },

   { { '&', 0 }, 79 },
   { { '&', 1 }, Standard_GlyphDeck_8b::TxtAmpX },

   { { '"', 0 }, 93 },
   { { '"', 1 }, Standard_GlyphDeck_8b::SqDqX },

   { { '*', 0 }, 82 },
   { { '*', 1 }, Standard_GlyphDeck_8b::TxtStarX },

   { { '+', 0 }, 75 },
   { { '+', 1 }, Standard_GlyphDeck_8b::TxtPlusX },

   { { '/', 0 }, 86 },
   { { '/', 1 }, Standard_GlyphDeck_8b::FslX },
   { { '/', 2 }, Standard_GlyphDeck_8b::Boundary },
   { { '/', 3 }, Standard_GlyphDeck_8b::SpaceX },
   { { '/', 4 }, Standard_GlyphDeck_8b::Null },
 };


 static QMap<QPair<char, u1>, quint8> static_64 {
   { { ':', 0 }, 71 },
   { { ':', 1 }, Standard_GlyphDeck_8b::NpColX },

   { { ';', 0 }, 72 },
   { { ';', 1 }, Standard_GlyphDeck_8b::NpSemX },

   { { '?', 0 }, 73 },
   { { '?', 1 }, Standard_GlyphDeck_8b::NpQmX },
   { { '?', 1 }, Standard_GlyphDeck_8b::IndQm },

   { { '<', 0 }, 88 },
   { { '<', 1 }, Standard_GlyphDeck_8b::NpLtX },

   { { '>', 0 }, 89 },
   { { '>', 1 }, Standard_GlyphDeck_8b::NpGtX },

   { { '=', 0 }, Standard_GlyphDeck_8b::TxtEqX },
   { { '=', 1 }, Standard_GlyphDeck_8b::TxtEqX },

   { { '@', 0 }, Standard_GlyphDeck_8b::TxtAtX },
   { { '@', 1 }, Standard_GlyphDeck_8b::TxtAtX },

 };

 static QMap<QPair<char, u1>, quint8> static_96 {
   { { '[', 0 }, 86 },
   { { '[', 1 }, Standard_GlyphDeck_8b::OSqBrX },

   { { ']', 0 }, 87 },
   { { ']', 1 }, Standard_GlyphDeck_8b::CSqBrX },

   { { '\\', 0 }, 90 },
   { { '\\', 1 }, Standard_GlyphDeck_8b::BslX },

   { { '^', 0 }, Standard_GlyphDeck_8b::TxtHatX },
   { { '^', 1 }, Standard_GlyphDeck_8b::TxtHatX },

   { { '_', 0 }, 37 },
   { { '_', 1 }, Standard_GlyphDeck_8b::NullX },

   { { '`', 0 }, Standard_GlyphDeck_8b::BqX },
   { { '`', 1 }, Standard_GlyphDeck_8b::BqX },
 };

 static QMap<QPair<char, u1>, quint8> static_127 {
   { { '{', 0 }, Standard_GlyphDeck_8b::OCyBrX },
   { { '{', 1 }, Standard_GlyphDeck_8b::OCyBrX },

   { { '|', 0 }, Standard_GlyphDeck_8b::PipeX },
   { { '|', 1 }, Standard_GlyphDeck_8b::PipeX },

   { { '}', 0 }, Standard_GlyphDeck_8b::CCyBrX },
   { { '}', 1 }, Standard_GlyphDeck_8b::CCyBrX },

   { { '~', 0 }, Standard_GlyphDeck_8b::TildeX },
   { { '~', 0 }, Standard_GlyphDeck_8b::TildeX },
 };

 

 u1 held_state = 0;

 u2 length_with_held_state = 0;
 u2 diacritic_code = 0;

 QString flags_acc;

 QMap<u4, QString> flags_strings;

 // //  held state codes: 
  //    0 -- nothing
  //    1-4 -- alt interpretation 1-4
  //    10 -- read alt interpretation
  //    11 -- done alt interpretation; maybe flags
  //    12 -- read flags
  //    13 -- flags acc
  //    20 -- diacritic start
  //    21 -- diacritic scope +
  //    22-4 -- diacritic scope 2-4
  //    201 -- 0 of 1
  //    202 -- 0 of 2
  //    203 -- 0 of 3
  //    212 -- 1 of 2
  //    213 -- 1 of 3
  //    223 -- 2 of 3

 for(char chr : src)
 {
  quint8 code = 0;

  if(held_state == 11)
  {
   if(chr == '~')
   {
    // //  we'll keep length_with_held_state 
     //    for future reference
    held_state = 12;
    continue;
   }
   length_with_held_state = 0;
   held_state = 0;
  }
  else if(held_state == 12)
  {
   if(chr == '(')
   {
    // //  Again, we'll keep length_with_held_state 
     //    for future reference
    held_state = 13;
    continue;
   }
   length_with_held_state = 0;
   held_state = 0;
  }
  else if(held_state == 13)
  {
   if(chr == ')')
   {
    // // store the acc;
    for(u2 i = 0; i < length_with_held_state; ++i)
    {
     flags_strings[index - i] = flags_acc;
    }
    flags_acc.clear();
    length_with_held_state = 0; 
    held_state = 0;
   }
   else
     flags_acc.append(QChar::fromLatin1(chr));
   continue;
  }
  else if(chr == '|')
  {
   if(held_state == 20)
     held_state = 0; // // || escape; no diacritic  
   else if(held_state == 0)
   { 
    held_state = 20; 
    continue;
   }    
  }
  
  if(held_state >= 20)
  {
   // //  part of a diacritic ...

   //    20 -- diacritic start
   //    22-4 -- diacritic scope 2-4
   //    201 -- 0 of 1
   //    202 -- 0 of 2
   //    203 -- 0 of 3
   //    212 -- 1 of 2
   //    213 -- 1 of 3
   //    223 -- 2 of 3

   switch(held_state)
   {
   case 20: 
    {
     u2 dcode;
     u1 length = get_diacritic_length_or_code(chr, dcode);
     if(length > 0)
     {
      if(code > 0)
      {
       diacritic_code = dcode;
       held_state = 210 + length; 
      }
      else
      {
       held_state = 20 + length;
      }
     }
     else
     {
      diacritic_code = dcode;
      held_state = 201;
     }
    }
    continue; // overall loop
   case 22:
    diacritic_code = get_diacritic_code(chr, 2);
    held_state = 202;
    continue; // overall loop
   case 23:
    diacritic_code = get_diacritic_code(chr, 3);
    held_state = 203;
    continue; // overall loop
   case 24:
    // //  to be determined ...
    exit(0);
    break;

   default:
    code = get_diacritic_cue_code(chr);
    code |= 64; // set dia bit ...
    break;   
   }
  }
  else if(chr < 48)
  {
   if( (held_state == 10) && (chr == '(') )
   {
    held_state = 1;
    continue;
   }
   if(held_state == 1)
   {
    if( (chr == ')') && (length_with_held_state > 0) )
    {
     held_state = 11;
     continue;
    }
   }

   code = static_47.value( {chr, held_state} );
   if(code == 0)
     continue;
  }
  else if(chr < 58)
  {
   // // (48 .. 58):  a digit
   code = chr - 48;
  }
  else if(chr < 65)
  {
   if( (held_state == 10) && (chr == '<') )
   {
    held_state = 4;
    continue;
   }
   if( (held_state == 4) && 
       (chr == '>') && (length_with_held_state > 0) )
   {
    held_state = 11;
    continue;
   }
   code = static_64.value( {chr, held_state} );
   if(code == 0)
     continue;
  }
  else if(chr < 91)
  {
   // //   (A .. Z)
   code = chr - 28;
  }
  else if(chr < 97)
  {
   if(chr == '`')
   {
    held_state = 10;
    continue;
   }
   if(chr == '[')
   {
    held_state = 3;
    continue;
   }
   if( (held_state == 3) && (chr == ']')
     && (length_with_held_state > 0) )
   {
    held_state = 11;
    continue;
   }
   code = static_96.value( {chr, held_state} );
   if(code == 0)
     continue;
  }
  else if(chr < 123)
  {
   // //   (a .. z)
   code = chr - 87;
  }
  else if(chr == '{')
  {
   if(held_state == 10)
   {
    held_state = 2;
    continue;
   }
   code = static_127.value( {chr, held_state} );
   if(code == 0)
     continue;
  }
  else if(chr == '}')
  {
   if( (held_state == 2) && (length_with_held_state > 0) )
   {
    held_state = 11;
    continue;
   }
   code = static_127.value( {chr, held_state} );
   if(code == 0)
     continue;
  }

  // // got code ...

  if(held_state >= 20)
  {
   // // we need to mark the diacritic
    //   also set the diacritic_code 
    //   anticipating next char in 2 or 3 length
   switch(held_state)
   {
   case 201:
    mark_diacritic_code(target, index, diacritic_code);
    diacritic_code = 0;
    held_state = 0;
    break;
   case 202:
    mark_diacritic_code(target, index, diacritic_code);
    diacritic_code = get_diacritic_code_inh(2, 2);
    held_state = 212;
    break;
   case 212:
    mark_diacritic_code(target, index, diacritic_code);
    diacritic_code = 0;
    held_state = 0;
    break;
   case 203:
    mark_diacritic_code(target, index, diacritic_code);
    diacritic_code = get_diacritic_code_inh(2, 3);
    held_state = 213;
    break;
   case 213:
    mark_diacritic_code(target, index, diacritic_code);
    diacritic_code = get_diacritic_code_inh(3, 3);
    held_state = 223;
    break;
   case 223:
    mark_diacritic_code(target, index, diacritic_code);
    diacritic_code = 0;
    held_state = 0;
    break;
   default: break;
   }
  }
  else if(held_state != 0)
    ++length_with_held_state;

  //current_deck_->encode()
  target[index] = code;
  ++index;  
 }
 last_index = index;
}

void HTXN_Document_8b::mark_diacritic_code(Glyph_Vector_8b& target, u4 index, u2 diacritic_code)
{
 u2 deck_code = dia_id_by_deck_[current_diacritic_deck_];
 target.add_diacritic(index, deck_code, diacritic_code);
}


void HTXN_Document_8b::encode_latin1(const QByteArray& src, 
  Glyph_Vector_8b& target, u2 gap)
{
 target.resize(src.size() + gap + 3);

 target[0] = Standard_GlyphDeck_8b::Boundary;

 u4 index = 1;
 while(index < gap + 1)
 {
  target[index] = Standard_GlyphDeck_8b::Space;
  ++index;
 } 
 target[index] = Standard_GlyphDeck_8b::Boundary;
 ++index;

 u4 last_index = index;

 encode_latin1(src, target, index, last_index);
 target[last_index] = Standard_GlyphDeck_8b::Boundary;
 target.resize(last_index + 1);
}

