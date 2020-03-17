
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include <QDebug>
#include <QFile>


#include "ngml-sdi/ngml-sdi-document.h"

#include <QDir>

#include "textio.h"

USING_KANS(TextIO)


//DEFAULT_SDI_FOLDER=

int main(int argc, char* argv[])
{
 NGML_SDI_Document nsd(DEFAULT_SDI_FOLDER "/ngml-sdi/t1.ngml.sdi.ntxh",
   DEFAULT_SDI_FOLDER "/ngml-sdi/t1");
 nsd.parse();

 return 0; 
}

