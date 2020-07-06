
// // license___here_h


#ifndef ViewToolDrawRect__H
#define ViewToolDrawRect__H


#include <QMouseEvent>

// package facsanadu.gui.view.tool;

/**
 * 
 * Tool to draw rectangle gates
 * 
 * @author Johan Henriksson
 *
 */
class ViewToolDrawRect : //implements ViewTool
{
 Gate* isDrawing_;// = nullptr;

 ViewWidget* w_;

public:
 
 ViewToolDrawRect(ViewWidget* w);
 
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
 
 //@Override
 bool allowHandle() Q_DECLARE_OVERRIDE;
};


#endif // __H
 

