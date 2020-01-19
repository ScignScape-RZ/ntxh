
#include "rz-ngml-whitespace-holder.h"

#include "rzns.h"

USING_RZNS(NGML)

NGML_Whitespace_Holder::NGML_Whitespace_Holder()
  : inherited_(nullptr)
{

}

void NGML_Whitespace_Holder::inherit_whitespace(NGML_Whitespace_Holder* wsh)
{
 inherited_ = wsh;
}


void NGML_Whitespace_Holder::attach_whitespace(QString whitespace)
{
 ws_ = NGML_Whitespace(whitespace);
}

