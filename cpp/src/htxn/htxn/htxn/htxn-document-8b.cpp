
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
 static QMap<char, quint8> static_47 {
  {'.', 65 },
 };
 target.resize(src.size());
 u4 index = 0;
 for(char chr : src)
 {
  quint8 code = 0;
  if(chr == 32)
  {
   code = 63;
  }
  else if(chr < 48)
  {
   code = static_47.value(chr);
   if(code == 0)
     continue;
   // //
    // continue;
  }
  else if(chr < 58)
  {
   // // (48 .. 58):  a digit
   code = chr - 48;
  }
  else if(chr < 65)
  {
   // //  continue;
  }
  else if(chr < 91)
  {
   // //   (A .. Z)
   code = chr - 28;
  }
  else if(chr < 97)
  {
   // //  continue;
  }
  else if(chr < 123)
  {
   // //   (a .. z)
   code = chr - 87;
   // //  continue;
  }
  else
  {
   // //  continue;
  }
  // // got code ...
  //current_deck_->encode()
  target[index] = code;
  ++index;  
 }
 target.resize(index);
}

