
// // license___here_h


#ifndef ViewTransform__H
#define ViewTransform__H



// package facsanadu.gui.view;

//import com.trolltech.qt.core.QPointF;

#include <QPointF>

class ViewSettings;


// //
class ViewTransform
{
 //How far the graph is pushed from the boundary (where labels are placed)

 int internalHeight_;
 int internalWidth_;
 int graphOffsetXY_;

 ViewSettings* viewsettings_;

public:

 ViewSettings* viewsettings()
 {
  return viewsettings_;
 }

 void set_viewsettings(ViewSettings* vs)
 {
  viewsettings_ = vs;
 }


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
 QPointF mapScreenToFcs(QPointF& pos);

 // // Map FCS value to screen space
 QPointF mapFcsToScreen(QPointF& pos);

 int mapFcsToScreenX(double x);
 int mapFcsToScreenY(double y);
 
 int mapGeneralToScreenX(double x);
 int mapGeneralToScreenY(double y); 
};

#endif // __H
 



