

//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "glyph-vector-8b.h"

#include "glyphdeck-base-8b.h"

USING_KANS(HTXN)


void Glyph_Vector_8b::check_external(u4 index, 
  GlyphDeck_Base_8b& current_deck, Glyph_Argument_Package& gap)
{
 u1 gp = value(index);
 current_deck.check_external(gp, gap);
 if(gap.flags.maybe_external_deck)
 {
  auto it = deck_map_.find(index);
  if(it == deck_map_.end())
  {
   auto iit = xx_map_.find(index);
   if(iit == xx_map_.end())
   {
    gap.flags.maybe_external_range = true;
    // look for a range ...
   }
   else
   {
    gap.flags.confirmed_external_extended = true;
    gap.flags.maybe_external_deck = false;
    gap.external_extended = iit.value();
   }
  }
  else
  {
   gap.flags.confirmed_external_deck = true;
   gap.flags.request_deck_resolve = true;
   gap.external_deck_code = it.value();    
   //gap.glyph_code = (u8) 
  }

 } 
}



