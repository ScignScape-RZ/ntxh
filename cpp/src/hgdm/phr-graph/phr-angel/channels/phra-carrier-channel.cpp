
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phra-carrier-channel.h"

#include "phra-carrier.h"


PHRA_Carrier_Channel::PHRA_Carrier_Channel(QString kind)
  :  kind_(kind), ref_count_(1)
{
}


void PHRA_Carrier_Channel::add_carrier(const std::string& type_name, 
  const std::string& symbol_name, u1 locator)
{
 PHRA_Carrier* pcr = new PHRA_Carrier;
 pcr->encode_symbol_name(QString::fromStdString(symbol_name));
 pcr->set_locator(locator);
 push_back(pcr);
}

void PHRA_Carrier_Channel::add_ref()
{
 // Increase the reference counter
 ref_count_++;
}
 
void PHRA_Carrier_Channel::release()
{
 // Decrease ref count and delete if it reaches 0
 if( --ref_count_ == 0 )
   delete this;
}

