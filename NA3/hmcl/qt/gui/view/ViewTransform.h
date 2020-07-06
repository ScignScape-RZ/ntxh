
// // license___here_h


#ifndef ViewTransform__H
#define ViewTransform__H



// package facsanadu.gui.view;

//import com.trolltech.qt.core.QPointF;

// //
class ViewTransform
{
 //How far the graph is pushed from the boundary (where labels are placed)

 int internalHeight_;
 int internalWidth_;

public:

 int graphOffsetXY = 30;
 
 ViewSettings viewsettings;

 // // Set the total view height
 void setTotalHeight(int h);
 
 // // Set the total view width
 void setTotalWidth(int w);

 // // Get the total height of the view
 int getTotalHeight();
 
 // // Set the total width of the view
 int getTotalWidth();

 double getTotalScaleX();
 double getTotalScaleY();
 
 // // Map screen space to FCS value
 QPointF mapScreenToFcs(QPointF pos);

 // // Map FCS value to screen space
 QPointF mapFcsToScreen(QPointF pos);

 int mapFcsToScreenX(double x);
 int mapFcsToScreenY(double y);
 
 int mapGeneralToScreenX(double x);
 int mapGeneralToScreenY(double y); 
};


