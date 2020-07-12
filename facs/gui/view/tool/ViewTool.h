
// // license___here_h


#ifndef ViewTool__H
#define ViewTool__H


#include <QMouseEvent>



// package facsanadu.gui.view.tool;

//import com.trolltech.qt.gui.QMouseEvent;

// // Tool for the view widget

class ViewTool
{
public:

 virtual void mousePressEvent(QMouseEvent* event) = 0;
 virtual void mouseReleaseEvent(QMouseEvent* ev) = 0;
 virtual void mouseMoveEvent(QMouseEvent* event) = 0;
 virtual void mouseDoubleClickEvent(QMouseEvent* event) = 0;
 virtual bool allowHandle() = 0;
};


#endif // __H
 


