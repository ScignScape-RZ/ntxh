
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef NGML_SDI_PAGE__H
#define NGML_SDI_PAGE__H

#include "global-types.h"


#include <QDebug>

#include <QTextStream>

#include "ngml-sdi-page-element.h"

#include <set>

#include "kans.h"

#include "accessors.h"

//KANS_CLASS_DECLARE(HGDMCore ,NTXH_Graph)
//USING_KANS(HGDMCore)

//class hypernode_type;

class NGML_SDI_Mark_Base; 

class NGML_SDI_Page 
{
 u4 number_;

 std::set<NGML_SDI_Page_Element> page_elements_;

public:
 
 NGML_SDI_Page(u4 number);

 ACCESSORS(u4 ,number)

 void add_page_element(NGML_SDI_Mark_Base* mark);

 void write(QString& contents);

 void read_page_element_from_strings(QStringList& strings);

};


#endif // NGML_SDI_PAGE__H
