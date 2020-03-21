
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "ngml-sdi-page.h"

#include "ngml-sdi-mark-base.h"

#include <QTextStream>

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

void NGML_SDI_Page::read_page_element_from_strings(QStringList& strings)
{
 qDebug() << strings;
 NGML_SDI_Mark_Base* mark = new NGML_SDI_Mark_Base;
 NGML_SDI_Page_Element el = NGML_SDI_Page_Element(mark);
 el.read_from_strings(strings);
 page_elements_.insert(el);
 qDebug() << "SX: " << el.mark()->start_x();  
}

void NGML_SDI_Page::write(QString& contents)
{
 QTextStream qts(&contents);

 int c = 0;
 for(const NGML_SDI_Page_Element& el : page_elements_)
 {
  ++c;
  NGML_SDI_Mark_Base& mark = *el.mark();
  
  qts << c << ' ' << mark.id() << ' ' << mark.start_x() 
    << ' ' << mark.start_y() << ' ' << mark.end_x() 
    << ' ' << mark.end_y() << '\n'; 
 }

 qDebug() << "Contents " << contents;
}

