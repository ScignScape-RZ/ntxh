package facsanadu.gui.view;

//import com.trolltech.qt.core.QPointF;

// //

ViewTransform::ViewTransform()
{
 //How far the graph is pushed from the boundary (where labels are placed)
 graphOffsetXY_ = 30;
 
 //ViewSettings viewsettings_;
 internalHeight_ = 0;
 internalWidth_ = 0;
}

void ViewTransform::setTotalHeight(int h)
{
 internalHeight=h-graphOffsetXY;
}
 
 /**
  * Set the total view width
  */
void ViewTransform::setTotalWidth(int w)
{
 internalWidth=w-graphOffsetXY;
}

 /**
  * Get the total height of the view
  */
int ViewTransform::getTotalHeight()
{
 return graphOffsetXY+internalHeight;
}
 
 /**
  * Set the total width of the view
  */
int ViewTransform::getTotalWidth()
{
 return graphOffsetXY+internalWidth;
}
 
double ViewTransform::getTotalScaleX()
{
 return viewsettings.scaleX*internalWidth; 
}

double ViewTransform::getTotalScaleY()
{
 return viewsettings.scaleY*internalHeight; 
}

 /**
  * Map screen space to FCS value
  */
QPointF ViewTransform::mapScreenToFcs(QPointF pos)
{
 int h=internalHeight-1;
 double x=(pos.x()-graphOffsetXY)/getTotalScaleX();
 double y=(h -pos.y())/getTotalScaleY();
 x=viewsettings.transformation.invert(x, viewsettings.indexX);
 y=viewsettings.transformation.invert(y, viewsettings.indexY);
 QPointF p=new QPointF(x,y);
 return p; 
}

 /**
  * Map FCS value to screen space
  */
QPointF ViewTransform::mapFcsToScreen(QPointF pos)
{
//  int h=internalHeight-1;
 QPointF p=new QPointF(
   mapFcsToScreenX(pos.x()),//  pos.x()*getTotalScaleX()+graphOffsetXY,
   mapFcsToScreenY(pos.y())//h - pos.y()*getTotalScaleY()
   );
 return p;
}

int ViewTransform::mapFcsToScreenX(double x)
{
 x=viewsettings.transformation.perform(x, viewsettings.indexX);
 return mapGeneralToScreenX(viewsettings.scaleX*x);
}

int ViewTransform::mapFcsToScreenY(double y)
{
 y=viewsettings.transformation.perform(y, viewsettings.indexY);
 return mapGeneralToScreenY(viewsettings.scaleY*y); 
}

 
int ViewTransform::mapGeneralToScreenX(double x)
{
 return graphOffsetXY+(int)(x*internalWidth);
}

int ViewTransform::mapGeneralToScreenY(double y)
{
 int h=internalHeight-1;
 return h-((int)(y*h));
}

