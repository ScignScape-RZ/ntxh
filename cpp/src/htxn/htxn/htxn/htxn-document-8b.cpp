
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "htxn-document-8b.h"

#include "standard-glyphdeck-8b.h"

#include "glyph-vector-8b.h"

#include "glyph-argument-package.h"


USING_KANS(HTXN)


HTXN_Document_8b::HTXN_Document_8b()
  :  current_deck_(0), 
     current_deck_code_(0),
     current_glyph_vector_(nullptr)
{

}

void HTXN_Document_8b::add_standard_deck()
{
 current_deck_ = new Standard_GlyphDeck_8b;
 decks_by_id_.push_back(current_deck_);
}

void HTXN_Document_8b::get_qstring_out(u4 layer, QString& result)
{
 Glyph_Vector_8b* gv = value(layer);
 if(!gv)
   return;
 //parse_layer(gv)
 Glyph_Argument_Package gap;
 gap.internal_deck = current_deck_;
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

void HTXN_Document_8b::read_layer(QString text, u2 gap)
{
 Glyph_Vector_8b* gv = new Glyph_Vector_8b;
 push_back(gv);
 current_glyph_vector_ = gv;
 encode_latin1(text.toLatin1(), *gv, gap);
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

 QString flags_acc;

 QMap<u4, QString> flags_strings;

 // //  held state codes: 
  //    0 -- nothing
  //    1-4 -- alt interpretation 1-4
  //    10 -- read alt interpretation
  //    11 -- done alt interpretation; maybe flags
  //    12 -- read flags
  //    13 -- flags acc

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
  
  if(chr < 48)
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

  if(held_state != 0)
    ++length_with_held_state;

  //current_deck_->encode()
  target[index] = code;
  ++index;  
 }
 last_index = index;
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

