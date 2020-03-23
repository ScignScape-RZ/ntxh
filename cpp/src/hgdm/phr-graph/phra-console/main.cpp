
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phr-angel/phra-runner.h"


int main(int argc, char* argv[])
{
 qDebug() << "Running ...";

 PHRA_Runner phrr;
// phrr.init_graph();
 phrr.run_script(PHRA_ROOT_DIR "/test.as");
 return 0;
}


