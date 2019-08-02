
//          Copyright Nathaniel Christen 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "ds-kdmi/ds-kdmi-model.h"
#include "ds-kdmi/ds-kdmi-model-qobject.h"

#include "kans.h"

USING_KANS(KDMI)

#include <QDebug>

#include "phaong.h"

typedef phaong_galaxy<QString> pgs_t;

int main(int argc, char **argv)
{
 KDMI_Model kdm;

   //   kdm.init_from_file(DEFAULT_NTXH_FOLDER  "/ctg.ngml.ntxh");
 // //  To demonstrate, initialize the kdmi via a QObject wrapper
 KDMI_Model_QObject kdq(&kdm);
 kdq.init_model_from_file(DEFAULT_NTXH_FOLDER  "/ctg.ngml.ntxh");

 return 0;
}
