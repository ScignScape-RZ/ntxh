
//          Copyright Nathaniel Christen 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "lexpair/lexpair-dialog.h"

#include "lexpair/lexpair-sxpr.h"

#include <QApplication>
#include <QDebug>



#include "kans.h"

#include "textio.h"

USING_KANS(TextIO)

#include <QThread>


USING_KANS(DSM)


int main(int argc, char **argv)
{
 QApplication qapp(argc, argv);

 qapp.setWindowIcon(QIcon(DEFAULT_ICON_FOLDER "/app-icon.png"));

 Lexpair_Dialog dlg(Lexpair_Dialog::split(
   "The home team won very quickly"), nullptr);

 dlg.show();
 return qapp.exec();
}
