
// // license___here_h


#ifndef ViewTool__H
#define ViewTool__H



// package facsanadu.gui.view.tool;

//import com.trolltech.qt.gui.QMouseEvent;

/**
 * 
 * Tool for the view widget
 * 
 * @author Johan Henriksson
 *
 */
class ViewTool
{
public:

 void mousePressEvent(QMouseEvent event) = 0;
 void mouseReleaseEvent(QMouseEvent ev) = 0;
 void mouseMoveEvent(QMouseEvent event) = 0;
 void mouseDoubleClickEvent(QMouseEvent event) = 0;
 bool allowHandle() = 0;
};


#endif // __H
 


