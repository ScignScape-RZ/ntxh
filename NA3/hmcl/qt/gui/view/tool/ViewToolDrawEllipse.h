
// // license___here_h


#ifndef ViewToolDrawEllipse__H
#define ViewToolDrawEllipse__H


// package facsanadu.gui.view.tool;

/**
 * 
 * Tool to draw ellipse gates
 * 
 * @author Johan Henriksson
 *
 */
class ViewToolDrawEllipse : //implements ViewTool
{
 Gate* isDrawing_;// = null;

 ViewWidget* w_;

 ViewToolDrawEllipse(ViewWidget w);

 /**
  * Mouse button released
  */
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

 bool allowHandle() Q_DECLARE_OVERRIDE;

};


