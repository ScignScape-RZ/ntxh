
#include "rz-ngml-whitespace.h"

#include <QDebug>

#include <bitset>

#include "rzns.h"

USING_RZNS(NGML)


NGML_Whitespace::NGML_Whitespace()
 : raw_text_(nullptr)
{

}

NGML_Whitespace::NGML_Whitespace(QString raw_text)
{
 parse(raw_text);
}

u1 NGML_Whitespace::get_length()
{
 int result = 0;
 if(raw_text_)
 {
  #ifdef NO_CAON
  result = raw_text_->size();
  #else //NO_CAON
  if(raw_text_.is_fixnum())
  {
   size_t v = raw_text_.get_fixnum();
   while(v > 0)
   {
    u1 encode = v & 3;
    if(encode > 0)
      ++result;
    v >>= 2;
   }
   return (u1) result;
  }
  else
   result = raw_text_->size();
  #endif //NO_CAON
  return (u1) qMin<int>(result, 255);
 }
 return 0;
}


QString NGML_Whitespace::to_string()
{
 if(raw_text_)
 {
  #ifdef NO_CAON
  return *raw_text_;
  #else //NO_CAON
  if(raw_text_.is_fixnum())
  {
   size_t v = raw_text_.get_fixnum();
   QString result;
   while(v > 0)
   {
    int encode = v & 3;
    switch(encode)
    {
    case 0:
     result += '\r'; break;
    case 1:
     result += ' '; break;
    case 2:
     result += '\t'; break;
    case 3:
     result += '\n'; break;
    }
    v >>= 2;
   }
   return result;
  }
  else
   return *raw_text_;
  #endif //NO_CAON
 }
 return QString();
}

//is_fixnum()

void NGML_Whitespace::parse(QString raw_text)
{
 size_t code = 0;
 int size = raw_text.size();
 if(size > 13)
 {
  raw_text_ = caon_ptr<QString>( new QString(raw_text) );
  return;
 }
 for(int i = 0; i < size; ++i)
 {
  int encode = 0;
  QChar qc = raw_text[i];
  switch(qc.toLatin1())
  {
  case '\r': break;
  case ' ': encode = 1; break;
  case '\t': encode = 2; break;
  case '\n': encode = 3; break;
  default:
   raw_text_ = caon_ptr<QString>( new QString(raw_text) );
   return;
  }
  encode <<= (i*2);
  code |= encode;
 }
 #ifdef NO_CAON
 //?raw_text_ = new QStringraw_text;
 #else //NO_CAON
 raw_text_.set_fixnum(code);
 #endif //NO_CAON
}
