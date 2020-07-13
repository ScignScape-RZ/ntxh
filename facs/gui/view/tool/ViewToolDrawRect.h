
// // license___here_h


#ifndef ViewToolDrawRect__H
#define ViewToolDrawRect__H

#include "ViewTool.h"

#include "events/FacsanaduEvent.h"


#include <QMouseEvent>

class Gate;

// package facsanadu.gui.view.tool;

/**
 * 
 * Tool to draw rectangle gates
 * 
 * @author Johan Henriksson
 *
 */
class ViewToolDrawRect : public ViewTool
{
 Gate* isDrawing_;// = nullptr;

 ViewWidget* vw_;

public:
 
 ViewToolDrawRect(ViewWidget* vw);
 
 /**
  * Mouse button released
  */
 void mouseReleaseEvent(QMouseEvent* ev) Q_DECL_OVERRIDE;

 void emitEvent(FacsanaduEvent e);

 /**
  * Mouse moved
  */
 void mouseMoveEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
 
 /**
  * Mouse button pressed
  */
 void mousePressEvent(QMouseEvent* event) Q_DECL_OVERRIDE;

 /**
  * Mouse button double-clicked
  */
 void mouseDoubleClickEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
 
 //@Override
 bool allowHandle() Q_DECL_OVERRIDE;
};


#endif // __H
 

