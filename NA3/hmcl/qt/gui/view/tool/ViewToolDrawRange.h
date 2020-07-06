
// // license___here_h


#ifndef ViewToolDrawRange__H
#define ViewToolDrawRange__H


// package facsanadu.gui.view.tool;


// // Tool to draw range gates
class ViewToolDrawRange: // implements ViewTool
{
 Gate* isDrawing_; //null;

 ViewWidget* w_;

public:

 ViewToolDrawRange(ViewWidget w);
 
 // //Mouse button released
 void mouseReleaseEvent(QMouseEvent ev);
 
 void emitEvent(FacsanaduEvent e);

 /**
  * Mouse moved
  */
 void mouseMoveEvent(QMouseEvent event);
 
 /**
  * Mouse button pressed
  */
 void mousePressEvent(QMouseEvent event);

 /**
  * Mouse button double-clicked
  */
 void mouseDoubleClickEvent(QMouseEvent event);
 
// @Override
 bool allowHandle();
}


