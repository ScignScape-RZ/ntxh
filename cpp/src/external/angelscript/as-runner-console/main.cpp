
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "as-runner/as-runner.h"


int main(int argc, char* argv[])
{
 AS_Runner asr;
 asr.run_script(AS_ROOT_DIR "/test.as");
 return 0;
}
