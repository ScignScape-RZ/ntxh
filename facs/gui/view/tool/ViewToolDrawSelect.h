
// // license___here_h


#ifndef ViewToolDrawSelect__H
#define ViewToolDrawSelect__H

#include "ViewTool.h"


#include <QMouseEvent>


// package facsanadu.gui.view.tool;


// //Tool to do nothing except selecting
class ViewToolDrawSelect : public ViewTool //implements ViewTool
{
 ViewWidget* vw_;

public:

 ViewToolDrawSelect(ViewWidget* vw);
 
 // //Mouse button released
 void mouseReleaseEvent(QMouseEvent* ev) Q_DECL_OVERRIDE;;

 // // Mouse moved
 void mouseMoveEvent(QMouseEvent* event) Q_DECL_OVERRIDE;;
 
 // // Mouse button pressed
 void mousePressEvent(QMouseEvent* event) Q_DECL_OVERRIDE;;

 // // Mouse button double-clicked
 void mouseDoubleClickEvent(QMouseEvent* event) Q_DECL_OVERRIDE;;
 
 //@Override
 bool allowHandle() Q_DECL_OVERRIDE;

};

#endif // __H
 


