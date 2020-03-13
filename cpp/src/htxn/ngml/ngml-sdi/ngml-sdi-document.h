
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef NGML_SDI_DOCUMENT__H
#define NGML_SDI_DOCUMENT__H

#include "global-types.h"


#include <QDebug>

#include <QTextStream>

#include "ntxh-parser/ntxh-document.h"

#include "kans.h"

KANS_CLASS_DECLARE(HGDMCore ,NTXH_Graph)

USING_KANS(HGDMCore)

#include "rzns.h"

//class hypernode_type;


class NGML_SDI_Document
{
 QString path_;
 u8 global_base_line_skip_;// = 12

public:
 
 NGML_SDI_Document(QString path);
 void parse();

 void parse_paragraph_start_hypernode(const NTXH_Graph& g, NTXH_Graph::hypernode_type* h);

 void parse_paragraph_end_hypernode(const NTXH_Graph& g, NTXH_Graph::hypernode_type* h);

 void parse_element_start_hypernode(const NTXH_Graph& g, NTXH_Graph::hypernode_type* h);

 void parse_element_end_hypernode(const NTXH_Graph& g, NTXH_Graph::hypernode_type* h);


 void parse_info_hypernode(const NTXH_Graph& g, NTXH_Graph::hypernode_type* h);

};


#endif // NGML_SDI_DOCUMENT__H
