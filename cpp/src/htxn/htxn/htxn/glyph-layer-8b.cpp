
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "glyph-layer-8b.h"

USING_KANS(HTXN)

Glyph_Layer_8b::Glyph_Layer_8b(u4 id)
 :  Flags(0), id_(id)
{

}

u4 Glyph_Layer_8b::get_range_by_enter(u4 enter, u4& leave)
{
 auto it = ranges_.find(enter);
 if(it == ranges_.end())
   return 0;
 leave = it.value().first().first;
 return it.value().first().second; 
}

void Glyph_Layer_8b::add_range(u4 enter, u4 leave, u4 node_code)
{
 ranges_[enter].push_back({leave, node_code});
}


