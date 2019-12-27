
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

void HTXN_Document_8b::read_glyph_point(Glyph_Argument_Package& gap, 
  u4 index, Glyph_Vector_8b& gv)
{
// gv.check_exterenal(index, *current_deck_, gap);
// if(gap.flags.

}

void HTXN_Document_8b::read_layer(QString text)
{
 Glyph_Vector_8b* gv = new Glyph_Vector_8b;
 push_back(gv);
 current_glyph_vector_ = gv;
 encode_latin1(text.toLatin1(), *gv);
}

void HTXN_Document_8b::encode_latin1(const QByteArray& src, 
  Glyph_Vector_8b& target)
{
 static QMap<QPair<char, u1>, quint8> static_47 {
  {  { '.', 0 }, 64 },
  {  { '.', 1 }, Standard_GlyphDeck_8b::NpDot },
  {  { '.', 1 }, Standard_GlyphDeck_8b::NsPer },

  {  { '!', 0 }, 65 },
  {  { '!', 1 }, Standard_GlyphDeck_8b::NpExcX },

  {  { '(', 0 }, 66 },
  {  { '(', 1 }, Standard_GlyphDeck_8b::NpOParX },

  {  { ')', 0 }, 67 },
  {  { '(', 1 }, Standard_GlyphDeck_8b::NpCParX },

  {  { '-', 0 }, 68 },
  {  { '-', 1 }, Standard_GlyphDeck_8b::DashSML },
  {  { '-', 2 }, Standard_GlyphDeck_8b::NpMinus },
  {  { '-', 3 }, Standard_GlyphDeck_8b::SnDash },

  {  { ',', 0 }, 69 },
  {  { ',', 1 }, Standard_GlyphDeck_8b::NpComX },

  {  { '\'', 0 }, 70 },
  {  { '\'', 1 }, Standard_GlyphDeck_8b::SqSqX },

  {  { '#', 0 }, 76 },
  {  { '#', 0 }, Standard_GlyphDeck_8b::TxtNumX },

  {  { '$', 0 }, 77 },
  {  { '$', 0 }, Standard_GlyphDeck_8b::TxtDolX },

  {  { '%', 0 }, 78 },
  {  { '%', 0 }, Standard_GlyphDeck_8b::TxtPerX },

  {  { '&', 0 }, 79 },
  {  { '&', 0 }, Standard_GlyphDeck_8b::TxtAmpX },

  {  { '"', 0 }, 93 },
  {  { '"', 1 }, Standard_GlyphDeck_8b::SqDqX },

  {  { '*', 0 }, 82 },
  {  { '*', 1 }, Standard_GlyphDeck_8b::TxtStarX },

  {  { '+', 0 }, 75 },
  {  { '+', 1 }, Standard_GlyphDeck_8b::TxtPlusX },

  {  { '/', 0 }, 90 },
  {  { '/', 1 }, Standard_GlyphDeck_8b::FslX },



 };


 static QMap<QPair<char, u1>, quint8> static_64 {
  {  { ':', 0 }, 71 },
  {  { ':', 1 }, Standard_GlyphDeck_8b::NpColX },

  {  { ';', 0 }, 72 },
  {  { ';', 1 }, Standard_GlyphDeck_8b::NpSemX },

  {  { '?', 0 }, 73 },
  {  { '?', 1 }, Standard_GlyphDeck_8b::NpQmX },
  {  { '?', 1 }, Standard_GlyphDeck_8b::IndQm },

  {  { '<', 0 }, 88 },
  {  { '<', 1 }, Standard_GlyphDeck_8b::NpLtX },

  {  { '>', 0 }, 89 },
  {  { '>', 1 }, Standard_GlyphDeck_8b::NpGtX },

  {  { '=', 0 }, Standard_GlyphDeck_8b::TxtEqX },
  {  { '=', 1 }, Standard_GlyphDeck_8b::TxtEqX },

  {  { '@', 0 }, Standard_GlyphDeck_8b::TxtAtX },
  {  { '@', 1 }, Standard_GlyphDeck_8b::TxtAtX },

 };

 static QMap<QPair<char, u1>, quint8> static_96 {
  {  { '[', 0 }, 86 },
  {  { '[', 1 }, Standard_GlyphDeck_8b::OSqBrX },

  {  { ']', 0 }, 87 },
  {  { ']', 1 }, Standard_GlyphDeck_8b::CSqBrX },

  {  { '\\', 0 }, 90 },
  {  { '\\', 1 }, Standard_GlyphDeck_8b::BslX },

  {  { '^', 0 }, Standard_GlyphDeck_8b::TxtHatX },
  {  { '^', 1 }, Standard_GlyphDeck_8b::TxtHatX },

  {  { '_', 0 }, 37 },
  {  { '_', 0 }, Standard_GlyphDeck_8b::NullX },

  {  { '`', 0 }, Standard_GlyphDeck_8b::BqX },
  {  { '`', 1 }, Standard_GlyphDeck_8b::BqX },
 };

 static QMap<QPair<char, u1>, quint8> static_127 {
  {  { '{', 0 }, Standard_GlyphDeck_8b::OCyBrX },
  {  { '{', 1 }, Standard_GlyphDeck_8b::OCyBrX },

  {  { '|', 0 }, Standard_GlyphDeck_8b::PipeX },
  {  { '|', 1 }, Standard_GlyphDeck_8b::PipeX },

  {  { '}', 0 }, Standard_GlyphDeck_8b::CCyBrX },
  {  { '}', 1 }, Standard_GlyphDeck_8b::CCyBrX },

  {  { '~', 0 }, Standard_GlyphDeck_8b::TildeX },
  {  { '~', 0 }, Standard_GlyphDeck_8b::TildeX },
 };


 target.resize(src.size());
 u4 index = 0;

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

  if(chr == 32)
  {
   code = 63;
   continue;
  }
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
   length_with_held_state = 0
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
      held_state = 11;
    continue;
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

  if(held_code != 0) 
    ++length_with_held_state;

  //current_deck_->encode()
  target[index] = code;
  ++index;  
 }
 target.resize(index);
}
