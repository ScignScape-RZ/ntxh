
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phra-carrier.h"

PHRA_Carrier::PHRA_Carrier()
  :  Flags(0), locator_(0), 
     type_or_context_(nullptr),
     symbol_encoding_(0)
{
}

QString PHRA_Carrier::get_symbol_name()
{
 if(!flags.encoded_symbol_name)  //((symbol_encoding_ % 1) == 0)
 { 
  if(!flags.full_symbol_info)
    return *(reinterpret_cast<QString*>(symbol_encoding_));
 }
 u1 len = symbol_encoding_ & 15;
 QString result = QString(len, QChar(' '));
 for(int i = 0, pos = 4; i < len; ++i, pos += 6)
 {
  u1 code = (symbol_encoding_ & ( ((u8) 63) << pos)) >> pos;
  if(code < 10) // // a digit 
    result.replace(i, 1, QChar::fromLatin1(code + 48));
  else if(code < 36) // // a .. z
    result.replace(i, 1, QChar::fromLatin1(code + 87));
  else if(code == 36)
    result.replace(i, 1, QChar('_'));
  else if(code == 63)
    result.replace(i, 1, QChar('-'));
  else // // A .. Z
    result.replace(i, 1, QChar::fromLatin1(code + 28));  
 }
 return result; 
}

void PHRA_Carrier::encode_symbol_name(QString name)
{
 flags.encoded_symbol_name = true;

 QByteArray qba = name.toLatin1();
 qba.truncate(10);

 symbol_encoding_ = qba.length();
 
 u1 sup = 0;
 
 int pos = 4;
 
 for(char chr : qba)
 {
  u1 code = 0;
  u1 supl = 0;

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
  else if(chr == 95) // // _
    code = 36;
  else if(chr < 97)
    supl = chr; 
  else if(chr < 123)
    // //   (a .. z)
    code = chr - 87;
  else 
    supl = chr; 

  if(supl > 0)
  {
   sup = supl;
   // // check supl ...
   code = 63;
  }
  symbol_encoding_ |= ( ((u8)code) << pos );
  pos += 6;   
 }
}
