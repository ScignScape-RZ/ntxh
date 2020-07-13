
// // license___here_h


#ifndef ViewToolDrawPoly__H
#define ViewToolDrawPoly__H

#include "ViewTool.h"

#include "events/FacsanaduEvent.h"


#include <QMouseEvent>


// package facsanadu.gui.view.tool;

// // Tool to draw polygon gates

class GatePolygon;


class ViewToolDrawPoly :  public ViewTool
{
 GatePolygon* isDrawing_;// = null;

 ViewWidget* vw_;

public:

 ViewToolDrawPoly(ViewWidget* vw);
 
 void mousePressEvent(QMouseEvent* event) Q_DECL_OVERRIDE;

 void mouseReleaseEvent(QMouseEvent* ev) Q_DECL_OVERRIDE;

 void emitEvent(FacsanaduEvent e);

 /**
  * Mouse moved
  */
 void mouseMoveEvent(QMouseEvent* event) Q_DECL_OVERRIDE;

 /**
  * Mouse button double-clicked
  */
 void mouseDoubleClickEvent(QMouseEvent* event) Q_DECL_OVERRIDE;

 //@Override
 bool allowHandle() Q_DECL_OVERRIDE;
 
};


#endif // __H
 

