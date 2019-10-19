
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include <QDebug>

//#include "patient.h"

//#include "whitedb.h"

#include <QCoreApplication>

#include <QDataStream>

#include "global-types.h"

#include "withs.h"

#include <QMap>
#include <QStringList>

#include "base32.h"


int main(int argc, char *argv[])
{
 QMap<QString, QStringList> args;
// QString enc;
 QStringRef enc;

 QString arg1;

 if(argc > 1)
   arg1 = QString::fromLatin1(argv[1]);

// qDebug() << arg1;

 if(arg1.startsWith("qargs="))
 {
 // enc = arg1.midRef(6);
  enc = arg1.midRef(6);
 }


 QByteArray qba;
 base32_decode_qstringref(enc, qba);
 QDataStream qds(qba);
 qds >> args;

 qDebug() << args;

 return 0;
}
