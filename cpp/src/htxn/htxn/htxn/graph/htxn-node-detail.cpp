
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "htxn-node-detail.h"

USING_KANS(HTXN)

HTXN_Node_Detail::HTXN_Node_Detail(u4 e, u4 l)
 :  Flags(0), enter(e), leave(l), node_ref(nullptr)
{

}

HTXN_Node_Detail::HTXN_Node_Detail()
 :  Flags(0), enter(0), leave(0), node_ref(nullptr)
{

}

QVector<u4>* HTXN_Node_Detail::get_refs_from_split() const
{
 QPair<Glyph_Layer_8b*, QVector<u4>>* pr = 
   static_cast<QPair<Glyph_Layer_8b*, QVector<u4>>*>(node_ref);
 return &pr->second;
}

QVector<u4>* HTXN_Node_Detail::get_refs() const
{
 return (flags.split_node_ref)? get_refs_from_split() : nullptr;
}

void HTXN_Node_Detail::add_node_ref(u4 nc)
{
 if(node_ref)
 {
  if(flags.split_node_ref)
  {
   QVector<u4>* refs = get_refs_from_split();
   refs->push_back(nc);
  }
  else
  {
   QPair<Glyph_Layer_8b*, QVector<u4>>* pr = new 
     QPair<Glyph_Layer_8b*, QVector<u4>>(
     {static_cast<Glyph_Layer_8b*>(node_ref), {nc}});
   node_ref = pr;
   flags.split_node_ref = true;
  }
 }
 else
 {
  node_ref = new 
    QPair<Glyph_Layer_8b*, QVector<u4>>({nullptr, {nc}});
  flags.split_node_ref = true;
 }
}

Glyph_Layer_8b* HTXN_Node_Detail::get_layer_from_split() const
{
 return 
   static_cast<QPair<Glyph_Layer_8b*, QVector<u4>>*>(node_ref)->first;
}

Glyph_Layer_8b* HTXN_Node_Detail::get_layer() const
{
 if(flags.split_node_ref)
   return get_layer_from_split();
 return static_cast<Glyph_Layer_8b*>(node_ref);
}

void HTXN_Node_Detail::set_layer(Glyph_Layer_8b* gl)
{
 if(flags.split_node_ref)
   static_cast<QPair<Glyph_Layer_8b*, QVector<u4>>*>(node_ref)
   ->first = gl;
 else
   node_ref = gl;
}

// u8 HTXN_Node_Detail::get_encoding()
// {
// u8 result = (enter << 32) | leave ;
// if(this.region)
//   result 
// }

// u8 HTXN_Node_Detail::get_raw_encoding()
// {
// u8 result = (u8) *this;
// return result;
// }

