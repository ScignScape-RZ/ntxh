
// // license___here

#include "ViewToolChoice.h"

#include "ViewToolDrawSelect.h"
#include "ViewToolDrawPoly.h"
#include "ViewToolDrawRect.h"
#include "ViewToolDrawRange.h"
#include "ViewToolDrawEllipse.h"


ViewTool* ViewToolChoice::getTool(ViewWidget* vw, ViewToolChoice::Enum e)
{
 if(e == Enum::SELECT)
   return new ViewToolDrawSelect(vw);

 else if(e == Enum::POLY)
   return new ViewToolDrawPoly(vw);

 else if(e == Enum::RECT)
   return new ViewToolDrawRect(vw);

 else if(e == Enum::RANGE)
   return new ViewToolDrawRange(vw);

 else if(e == Enum::ELLIPSE)
   return new ViewToolDrawEllipse(vw);

 else
   return nullptr; // throw new RuntimeException("Unsupported tool");
}


