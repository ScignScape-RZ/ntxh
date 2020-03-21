
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "ngml-sdi-page-element.h"

#include "ngml-sdi-mark-base.h"

//#include "ntxh-parser/ntxh-document.h"

#include "global-types.h"

#include <vector>

//typedef NTXH_Graph::hypernode_type hypernode_type;

NGML_SDI_Page_Element::NGML_SDI_Page_Element(NGML_SDI_Mark_Base* mark)
  :  mark_(mark), count_in_page_(0)
{
}

void NGML_SDI_Page_Element::read_from_strings(QStringList& qsl)
{
 std::vector<u4> nums(6);
 std::transform(qsl.begin(), qsl.end(), 
   nums.begin(), [](const QString& qs)
   {
    return qs.toInt();
   });
 mark_->set_id(nums[1]);
 mark_->set_start_x(nums[2]);
 mark_->set_start_y(nums[3]);
 mark_->set_end_x(nums[4]);
 mark_->set_end_y(nums[5]);
}

QPair<u4, u4> NGML_SDI_Page_Element::get_minimal_vertical_compare_offset(QPair<u4, u4> new_values)
{
 static QPair<u4, u4> the_values = {4, 2};
 if(new_values.first)
   the_values = new_values;
 return the_values;
} 

bool operator <(const NGML_SDI_Page_Element& lhs, 
  const NGML_SDI_Page_Element& rhs)
{ 
 QPair<u4, u4> pr = NGML_SDI_Page_Element::get_minimal_vertical_compare_offset();
 u4 offset = pr.first;
 u4 trigger = pr.second;

 const NGML_SDI_Mark_Base& lm = *lhs.mark();
 const NGML_SDI_Mark_Base& rm = *rhs.mark();

 u4 lsy = lm.start_y();
 u4 rsy = rm.start_y();

 while(offset > 0)
 {
  if(lsy < rsy - offset)
    return true;
  if(rsy < lsy - offset)
    return false;
  
  // // trigger means the starts are almost 
   //   indistinguishable so compare via the ends ...
  if(offset > trigger)
    continue;
  
  u4 lsx = lm.start_x();
  u4 rsx = rm.start_x();

  if(lsx < rsx - offset)
    return true;
  if(rsx < lsx - offset)
    return false;
 }
 return false;
}

