
// // license___here_h


#ifndef ViewToolDrawSelect__H
#define ViewToolDrawSelect__H


// package facsanadu.gui.view.tool;


// //Tool to do nothing except selecting
class ViewToolDrawSelect : ViewTool //implements ViewTool
{
 ViewWidget* w;

 ViewToolDrawSelect(ViewWidget w);
 
 // //Mouse button released
 void mouseReleaseEvent(QMouseEvent ev);

 // // Mouse moved
 void mouseMoveEvent(QMouseEvent event);
 
 // // Mouse button pressed
 void mousePressEvent(QMouseEvent event);

 // // Mouse button double-clicked
 void mouseDoubleClickEvent(QMouseEvent event);
 
 //@Override
 bool allowHandle() Q_DECLARE_OVERRIDE;

};

