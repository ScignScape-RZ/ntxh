
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phra-carrier-channel.h"

#include "phra-carrier.h"
#include "phra-binary-channel.h"
#include "contexts/phra-value-context.h"

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

PHRA_Binary_Channel* PHRA_Carrier_Channel::to_binary(PHRA_Value_Context* pvc)
{
 PHRA_Binary_Channel* result = new PHRA_Binary_Channel;
 for(PHRA_Carrier* pcr : *this)
 {
  QString sn = pcr->get_symbol_name();
  qDebug() << "SN: " << sn;
  u1 loc = pcr->locator();
  pvc->locator_to_binary(*result, loc);
  u2 test = result->extract_2(1);
  qDebug() << "test = " << test;
 }
 return result;
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

