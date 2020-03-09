
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef NGML_SDI_DOCUMENT__H
#define NGML_SDI_DOCUMENT__H


#include "ngml-sdi-document.h"


#include <QDebug>

#include <QTextStream>

#include "textio.h"
USING_KANS(TextIO)

#include "ntxh-parser/ntxh-document.h"

#include "kans.h"
USING_KANS(HGDMCore)

#include "rzns.h"


class NGML_SDI_Document
{
 QString path_;

public:
 
 NGML_SDI_Document(QString path);
 void parse();

};


#endif // NGML_SDI_DOCUMENT__H
