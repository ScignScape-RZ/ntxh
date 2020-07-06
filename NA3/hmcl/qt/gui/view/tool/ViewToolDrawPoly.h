
// // license___here_h


#ifndef ViewToolDrawPoly__H
#define ViewToolDrawPoly__H


// package facsanadu.gui.view.tool;

/**
 * 
 * Tool to draw polygon gates
 * 
 * @author Johan Henriksson
 *
 */

class ViewToolDrawPoly :// implements ViewTool
{
 GatePolygon* isDrawing_;// = null;

 ViewWidget* w_;

public:

 ViewToolDrawPoly(ViewWidget* w);
 
 /**
  * Mouse button pressed
  */

 void mousePressEvent(QMouseEvent event);
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
  * Mouse button double-clicked
  */
 void mouseDoubleClickEvent(QMouseEvent event);

 //@Override
 bool allowHandle() Q_DECLARE_OVERRIDE;
 
}
