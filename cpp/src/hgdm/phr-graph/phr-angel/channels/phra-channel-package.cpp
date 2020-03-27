
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phra-channel-package.h"

#include "phra-carrier-channel.h"


PHRA_Channel_Package::PHRA_Channel_Package()
  :  ref_count_(0)
{
}

void PHRA_Channel_Package::add_fname(const std::string& name)
{
 fname_ = QString::fromStdString(name);
}

PHRA_Carrier_Channel* PHRA_Channel_Package::add_carrier_channel(QString kind)
{
 return new PHRA_Carrier_Channel(kind);
}

void PHRA_Channel_Package::add_ref()
{
 // Increase the reference counter
 ref_count_++;
}
 
void PHRA_Channel_Package::release()
{
 // Decrease ref count and delete if it reaches 0
 if( --ref_count_ == 0 )
   delete this;
}

