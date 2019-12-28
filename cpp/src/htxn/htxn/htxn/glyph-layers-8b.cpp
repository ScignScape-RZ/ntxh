
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "glyph-layers-8b.h"

#include "glyph-vector-8b.h"

#include "glyph-argument-package.h"

#include "glyphdeck-base-8b.h"

#include "kans.h"

#include <QString>
#include <QList>
#include <QVector>

#include <functional>

//class WCM_WhiteDB;

USING_KANS(HTXN)

Glyph_Layers_8b::Glyph_Layers_8b()
{

}


void Glyph_Layers_8b::get_htxne_out(Glyph_Vector_8b& gv, 
  u4 index, Glyph_Argument_Package& gap)
{
 GlyphDeck_Base_8b& deck = *gap.internal_deck;
 gv.check_external(index, deck, gap);
// if(gap.no_flags())
// {
//  deck.get_htxne_out((u1)gap.glyph_code, gap);
// }

 

 deck.get_htxne_out((u1)gap.glyph_code, gap);



}


void Glyph_Layers_8b::get_qstring_out(Glyph_Vector_8b& gv, 
  u4 index, Glyph_Argument_Package& gap)
{
 GlyphDeck_Base_8b& deck = *gap.internal_deck;
// if(numeral_diacritic_code_)
//   gv.check_external(index, deck, gap);
// else
//   ;//gv.check_external_excluding_numeral_diacritic(index, deck, gap);
 gv.check_external(index, deck, gap);
 if(gap.no_flags())
 {
  deck.get_qstring_out((u1)gap.glyph_code, gap);
 }

#ifdef HIDE
 if(gap.flags.request_deck_resolve)
 {
  auto it = decks_by_id_.find(gap.external_deck_code);
  if(it == decks_by_id_.end())
  {
   return;
  }
  else
  {

  }
 }
 else if(gap.flags.request_deck_resolve)
#endif //def HIDE

}

void Glyph_Layers_8b::get_latex(u4 layer, u4 index, 
  Glyph_Argument_Package& gap)
{
 Glyph_Vector_8b* vec = value(layer);
 if(!vec)
 {
  gap.str = "?";
   return;

 }
// vec->check_external(index, gap);
// if(gap.flags.request_deck_resolve)
// {
//  auto it = decks_by_id_.find(gap.external_deck_code);
//  if(it == decks_by_id_.end())
//  {
//   return
//  }
//  else
//  {

//  }

// }
}



