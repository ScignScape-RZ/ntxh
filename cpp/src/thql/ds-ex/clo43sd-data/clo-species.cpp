
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "clo-species.h"

//#include "wcm/wcm-hyponode.h"

CLO_Species::CLO_Species()
  :  current_view_minimum_(0), current_view_maximum_(0)
{

}

u2 CLO_Species::view_offset = 10;

QPair<u4, u4> CLO_Species::get_view_range()
{
 if( (current_view_minimum_ == 0)
   | (current_view_maximum_ == 0))
  return  {0, 0};
 return {current_view_minimum_ - 1, current_view_maximum_};
}


QString CLO_Species::get_view_min_max_string()
{
 if( (current_view_minimum_ == 0)
   | (current_view_maximum_ == 0))
   return "N/A";
 return QString("%1 - %2").arg(current_view_minimum_).arg(current_view_maximum_);
}



//WCM_Hyponode** CLO_Species::as_hyponode_array()
//{
// WCM_Hyponode** result = new WCM_Hyponode*[3];
// result[0] = new WCM_Hyponode;
// result[0]->set_wgdb_encoding({});

// result[1] = new WCM_Hyponode;
// result[1]->set_qt_encoding();

// result[2] = new WCM_Hyponode;
// result[2]->set_qt_encoding();

//}
