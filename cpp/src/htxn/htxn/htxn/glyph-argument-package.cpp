
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "glyph-argument-package.h"

USING_KANS(HTXN)

Glyph_Argument_Package::Glyph_Argument_Package()
 :  Flags(0), external_extended(nullptr), 
    external_deck_code(0), 
    external_diacritic_code(0), 
    glyph_code(0), internal_deck(nullptr)
{

}

void Glyph_Argument_Package::reset_most()
{
 Flags ^= 0b111111111;

 chr = QChar();
 str.clear();
 external_extended = nullptr;
 external_deck_code = 0;
 external_diacritic_code = 0;
 glyph_code = 0;
}

void Glyph_Argument_Package::reset()
{
 Flags = 0;
 chr = QChar();
 str.clear(); 
 external_extended = nullptr;
 external_deck_code = 0;
 external_diacritic_code = 0;
 glyph_code = 0;
// internal_deck = nullptr;
// external_deck = 0;
// external_diacritic = 0;
}


