
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHR_DIRECT_EVAL__H
#define PHR_DIRECT_EVAL__H


#include "kans.h"


KANS_(Phaon)

class PHR_Code_Model;
class PHR_Command_Package;
class PHR_Symbol_Scope;

void phr_direct_eval(PHR_Code_Model* pcm,
  PHR_Command_Package* pcp, PHR_Symbol_Scope* pss);

_KANS(Phaon)

#endif //PHR_DIRECT_EVAL__H
