// package facsanadu.gui.view.tool;

ViewToolDrawPoly::ViewToolDrawPoly(ViewWidget* w)
{
 isDrawing_ = nullptr;

 w_ = w;
}
 
 /**
* Mouse button pressed
*/
void ViewToolDrawPoly::mousePressEvent(QMouseEvent event)
{
 if(event.button()==MouseButton.LeftButton && !w.viewsettings.isHistogram())
 {
  QPointF p = w.trans.mapScreenToFcs(event.posF()); 
 
  boolean justcreated=false;
  GatePolygon g;
  if(isDrawing_ != nullptr)
    g=isDrawing;
  else
  { 
   justcreated=true;
   g=new GatePolygon();
   g.indexX=w.getIndexX();
   g.indexY=w.getIndexY();
   isDrawing=g;
   w.addGate(g);
   g.setUniqueColor();
  }
  g.addPoint(p.x(), p.y());
  if(justcreated)
    g.addPoint(p.x(), p.y());
  g.updateInternal();
 
  w.sendEvent(new EventGatesMoved());
 }
}

 /**
* Mouse button released
*/
void ViewToolDrawPoly::mouseReleaseEvent(QMouseEvent ev)
{
 emitEvent(new EventGatesChanged());
}

void ViewToolDrawPoly::emitEvent(FacsanaduEvent e)
{
 w.mainWindow.handleEvent(e);
}

 /**
* Mouse moved
*/
void ViewToolDrawPoly::mouseMoveEvent(QMouseEvent event)
{
 if(isDrawing!=null)
 {
  GatePolygon g=isDrawing;
 
  QPointF p = w.trans.mapScreenToFcs(event.posF()); 

  g.setPoint(g.getNumPoints()-1, p.x(), p.y());
  g.updateInternal();
  emitEvent(new EventGatesMoved());
 }
}


 /**
* Mouse button double-clicked
*/
void ViewToolDrawPoly::mouseDoubleClickEvent(QMouseEvent event)
{
 if(isDrawing!=null)
 {
  isDrawing.removeRedundantPoints();
  isDrawing=null;
  w.sendEvent(new EventSetViewTool(ViewToolChoice.SELECT));
  emitEvent(new EventGatesChanged());
 }
}


bool ViewToolDrawPoly::allowHandle()
{
 return isDrawing==null;
}

 
 
 
 }
