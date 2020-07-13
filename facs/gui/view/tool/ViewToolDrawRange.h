
// // license___here_h


#ifndef ViewToolDrawRange__H
#define ViewToolDrawRange__H


#include "ViewTool.h"

#include "events/FacsanaduEvent.h"


#include <QMouseEvent>


// package facsanadu.gui.view.tool;


// // Tool to draw range gates
class ViewToolDrawRange : public ViewTool
{
 Gate* isDrawing_; //null;

 ViewWidget* vw_;

public:

 ViewToolDrawRange(ViewWidget* vw);
 
 // //Mouse button released
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
 
// @Override
 bool allowHandle() Q_DECL_OVERRIDE;
};


#endif // __H
 



