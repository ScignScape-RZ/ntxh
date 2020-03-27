
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef PHRA_CHANNEL_RUNNER__H
#define PHRA_CHANNEL_RUNNER__H

#include <QDebug>
#include <QString>

#include "accessors.h"

#include "global-types.h"

class PHRA_Binary_Channel;
class PHRA_Function_Table;


class PHRA_Channel_Runner
{
 QString fname_;
 PHRA_Binary_Channel& pbc_;
 PHRA_Function_Table& pft_;
 
public:

 PHRA_Channel_Runner(PHRA_Function_Table& pft, 
   PHRA_Binary_Channel& pbc); 

 ACCESSORS(QString ,fname)

 void run(u8 mh);

};


#endif //  PHRA_CHANNEL_RUNNER__H

