
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "clo-species-display-info.h"

//#include "wcm/wcm-hyponode.h"

CLO_Species_Display_Info::CLO_Species_Display_Info()
  :  current_view_minimum_(0), current_view_maximum_(0), cursor_({0,0})
{

}

u2 CLO_Species_Display_Info::view_offset = 10;

QPair<u4, u4> CLO_Species_Display_Info::get_view_range()
{
 if( (current_view_minimum_ == 0)
   | (current_view_maximum_ == 0))
  return  {0, 0};
 return {current_view_minimum_ - 1, current_view_maximum_};
}


QString CLO_Species_Display_Info::get_view_min_max_string()
{
 if( (current_view_minimum_ == 0)
   | (current_view_maximum_ == 0))
   return "N/A";
 return QString("%1 - %2").arg(current_view_minimum_).arg(current_view_maximum_);
}


