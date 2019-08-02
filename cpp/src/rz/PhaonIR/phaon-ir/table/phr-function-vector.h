
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHR_FUNCTION_VECTOR__H
#define PHR_FUNCTION_VECTOR__H


#include "kans.h"

#include "accessors.h"

#include "relae-graph/relae-caon-ptr.h"

#include <QVector>

#include <QSet>

#include "phr-function.h"

KANS_(Phaon)

class PHR_Type_Object;

class PHR_Function_Vector : public QVector<PHR_Function>
{

public:

 PHR_Function_Vector();

 PHR_Function_Vector(PHR_Function& phf);

 void* match_against_codes(const QSet<int>& codes, int& mc, int& rbc,
   const PHR_Type_Object** ppto = nullptr);

 void* find_argvec_function(int& mc, int& rbc,
   const PHR_Type_Object** ppto = nullptr);

 void* get_first();

};

_KANS(Phaon)


#endif //PHR_FUNCTION_VECTOR__H
