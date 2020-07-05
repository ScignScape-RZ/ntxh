// package facsanadu.gui.view.tool;


ViewToolDrawRange::ViewToolDrawRange(ViewWidget* w)
{
 isDrawing_ = nullptr;
 w_ = w;
}

 // //Mouse button released
void ViewToolDrawRange::mouseReleaseEvent(QMouseEvent ev)
{
 isDrawing=null;
 w.sendEvent(new EventSetViewTool(ViewToolChoice.SELECT));
 emitEvent(new EventGatesChanged());
}
 
void ViewToolDrawRange::emitEvent(FacsanaduEvent e)
{
 w.mainWindow.handleEvent(e);

}

 /**
  * Mouse moved
  */
void ViewToolDrawRange::mouseMoveEvent(QMouseEvent event)
{
 if(isDrawing!=null)
 {
  GateRange grect=(GateRange)isDrawing;
  
  QPointF p = w.trans.mapScreenToFcs(event.posF()); 
  
  grect.x2=p.x();
  grect.updateInternal();
  w.sendEvent(new EventGatesMoved());
 }
}
 
 /**
  * Mouse button pressed
  */
void ViewToolDrawRange::mousePressEvent(QMouseEvent event)
{
 if(event.button()==MouseButton.LeftButton)
 {
  QPointF p = w.trans.mapScreenToFcs(event.posF()); 
  
  GateRange grect=new GateRange();
  grect.index=w.getIndexX();
  grect.x1=grect.x2=p.x();
  grect.updateInternal();
  isDrawing=grect;

  w.addGate(grect);
  grect.setUniqueColor();
  emitEvent(new EventGatesMoved());
 }
}

 /**
  * Mouse button double-clicked
  */
void ViewToolDrawRange::mouseDoubleClickEvent(QMouseEvent event)
{

}
 
// @Override
bool ViewToolDrawRange::allowHandle()
{
 return isDrawing==null;
}


