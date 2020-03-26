
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phra-carrier.h"

PHRA_Carrier::PHRA_Carrier()
  :  locator_(0), 
     type_or_context_(nullptr),
     symbol_encoding_(0)
{
}

void PHRA_Carrier::encode_symbol_name(QString name)
{
 QByteArray qba = name.toLatin1();
 qba.truncate(10);

 symbol_encoding_ = 1;
 
 u1 supl = 0;
 
 int pos = 4;
 
 for(char chr : qba)
 {
  u1 code = 0;

  if(chr < 48)
    supl = chr;
  else if(chr < 58)
    // // (48 .. 58):  a digit
    code = chr - 48;
  else if(chr < 65)
    supl = chr; 
  else if(chr < 91)
    // //   (A .. Z)
    code = chr - 28;
  else
    supl = chr; 

  if(code == 0)
  {
   // // check supl ...
   code = 63;
  }
  symbol_encoding_ |= (code << pos);
  pos += 6;   
 }
}
