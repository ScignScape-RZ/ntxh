
#include "htxn-document-8b.h"

#include "standard-glyph-deck-8b"

#include "glyph-vector-8b"


HTXN_Document_8b::HTXN_Document_8b()
  :  current_deck_(0), 
     current_deck_code_(nullptr), 
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
  get_qstring_out(*gv, index, gap);
  if(gap.chr.isNull())
    result.append(gap.str);
  else
    result.append(gap.chr);
 } 
}

void HTXN_Document_8b::read_glyph_point(Glyph_Argument_Package& gap, 
  u4 index, Glyph_Vector_8b& gv)
{
 gv.check_exterenal(index, *current_deck_, gap);
 if(gap.flags.

}

void HTXN_Document_8b::read_layer(QString text)
{
 Glyph_Vector_8b* gv = new Glyph_Vector_8b;
 push_back(gv);
 current_glyph_vector_ = gv;
 encode_latin1(text, *gv);
}

void HTXN_Document_8b::encode_latin1(const QByteArray& src, 
  Glyph_Vector_8b& target)
{
 target.reserve(src.size())
 u4 index = 0;
 for(char chr : src)
 {
  quint8 code = 0;
  if(chr < 48)
  {
   // //
   continue;
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
   code = chr + 39;
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
}

