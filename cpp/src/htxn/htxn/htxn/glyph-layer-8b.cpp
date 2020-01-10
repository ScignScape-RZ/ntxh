
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

void Glyph_Layer_8b::write_ranges(QTextStream& qts) const
{

}

void Glyph_Layer_8b::read_ranges(QTextStream& qts)
{

}


void Glyph_Layer_8b::add_leave(u4 leave, QString cmd, const HTXN_Node_Detail* nd)
{
 processing_leaves_[leave].push_back({cmd, nd});
}

QVector<QPair<QString, const HTXN_Node_Detail*>> Glyph_Layer_8b::check_leave(u4 leave)
{
 return processing_leaves_.value(leave);
}

u4 Glyph_Layer_8b::get_range_by_enter(u4 enter, u4& leave, u2 count)
{
 auto it = ranges_.find(enter);
 if(it == ranges_.end())
   return 0;
 if(count >= it.value().size())
   return 0;
 leave = it.value()[count].first;
 return it.value()[count].second;
}

void Glyph_Layer_8b::add_range(u4 enter, u4 leave, u4 node_code)
{
 ranges_[enter].push_back({leave, node_code});
}


