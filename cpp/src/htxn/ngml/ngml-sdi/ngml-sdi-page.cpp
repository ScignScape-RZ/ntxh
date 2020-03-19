
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "ngml-sdi-page.h"

//#include "ntxh-parser/ntxh-document.h"

#include "global-types.h"

//typedef NTXH_Graph::hypernode_type hypernode_type;

NGML_SDI_Page::NGML_SDI_Page(u4 number)
  :  number_(number)
{
}

void NGML_SDI_Page::add_page_element(NGML_SDI_Mark_Base* mark)
{
 page_elements_.insert({mark});
}

void NGML_SDI_Page::write(QString& contents)
{
 
}

