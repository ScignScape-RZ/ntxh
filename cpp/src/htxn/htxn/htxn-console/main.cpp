
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include <QDebug>

#include "htxn/htxn-document-8b.h"

int main(int argc, char *argv[])
{
 HTXN_Document_8b doc;
 doc.read_layer("This is a text layer");

 QString out;
 doc.get_qstring_out(out);

 qDebug() << out;

 return 0;
}
