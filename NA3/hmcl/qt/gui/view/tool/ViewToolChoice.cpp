
ViewTool getTool(ViewWidget w, ViewToolChoice t)
{
 if(t==ViewToolChoice.SELECT)
   return new ViewToolDrawSelect(w);
 else if(t==ViewToolChoice.POLY)
   return new ViewToolDrawPoly(w);
 else if(t==ViewToolChoice.RECT)
   return new ViewToolDrawRect(w);
 else if(t==ViewToolChoice.RANGE)
   return new ViewToolDrawRange(w);
 else if(t==ViewToolChoice.ELLIPSE)
   return new ViewToolDrawEllipse(w);
 else
   throw new RuntimeException("Unsupported tool");
}
