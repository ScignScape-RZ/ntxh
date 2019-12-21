
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "standard-glyphpack.h"

USING_KANS(HTXN)

Standard_GlyphPack_8b::Standard_GlyphPack_8b(u1 code)
 :  code_(code)
{

}

u1 Standard_GlyphPack_8b::get_latex_cue()
{
 if( (code_ & 128) > 0 )
 {
  return 255;
 }
 if( (code_ & 64) > 0 )
 {
  return 255;
 }
 //if(code == 63)
 return code_;
}

u1 Standard_GlyphPack_8b::get_xml_cue()
{

}

u1 Standard_GlyphPack_8b::get_diacritic_code_cue()
{

}





