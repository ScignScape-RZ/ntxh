
// // license___here_h

#include "GateRendererRect.h"

#include "GateHandle.h"

#include "../gates/GateRect.h"

#include "../ViewSettings.h"
#include "../ViewTransform.h"


// package facsanadu.gui.view.gate;

// // Renderer for rectangular gates

class GateHandle_1 : public GateHandle
{
 QPointF p1;

public:


 GateHandle_1(QPointF p) : p1(p) {}

 void move2(MainWindow* w, double dx, double dy) Q_DECL_OVERRIDE;
 /*  {
   if(viewsettings->indexX()==cg->indexX)
   cg->x1=dx;
   else if(viewsettings->indexY()==cg->indexX)
   cg->y1=dx;
   
   if(viewsettings->indexX()==cg->indexY)
   cg->x1=dy;
   else if(viewsettings->indexY()==cg->indexY)
   cg->y1=dy;
   
   gate->updateInternal();
   w.handleEvent(new EventGatesMoved());
   }
  */
 
 double getX() Q_DECL_OVERRIDE
 {
  return p1.x();//x[0];
 }

 double getY() Q_DECL_OVERRIDE
 {
  return p1.y();//y[0];
 }
};

class GateHandle_2 : public GateHandle
{
 QPointF p2;

public:


 GateHandle_2(QPointF p) : p2(p) {}

 void move2(MainWindow* w, double dx, double dy) Q_DECL_OVERRIDE;
 /*  public void move2(MainWindow w, double dx, double dy)
   {
   if(viewsettings->indexX()==cg->indexX)
     cg->x2=dx;
   else if(viewsettings->indexY()==cg->indexX)
     cg->y2=dx;
   
   if(viewsettings->indexX()==cg->indexY)
     cg->x2=dy;
   else if(viewsettings->indexY()==cg->indexY)
     cg->y2=dy;
   
   gate->updateInternal();
   w.handleEvent(new EventGatesMoved());
   }
 */

 double getX() Q_DECL_OVERRIDE
 {
  return p2.x();
 }

 double getY() Q_DECL_OVERRIDE
 {
  return p2.y();
 }
};



void GateRendererRect::render(const Gate* gate, QPainter& p, ViewTransform* w, 
   const ViewSettings* viewsettings, QList<GateHandle*> handles)
{
 const GateRect* cg = (GateRect*) gate;
 
 if(viewsettings->coversXandY( cg->indexX, cg->indexY ))
 {
  //Figure out which dimension is what
  QList<double> x {0, 0};
  QList<double> y {0, 0};

  if(viewsettings->indexX() == cg->indexX)
  {
   x[0] = cg->x1;
   x[1] = cg->x2;
  }
  if(viewsettings->indexY() == cg->indexX)
  {
   y[0] = cg->x1;
   y[1] = cg->x2;
  }
  
  if(viewsettings->indexX()==cg->indexY)
  {
   x[0] = cg->y1;
   x[1] = cg->y2;
  }
  if(viewsettings->indexY()==cg->indexY)
  {
   y[0] = cg->y1;
   y[1] = cg->y2;
  }

  QPointF p1 = w->mapFcsToScreen( QPointF(x[0], y[0]) );
  QPointF p2 = w->mapFcsToScreen( QPointF(x[1], y[1]) );
  
  p.drawRect( QRectF(p1, p2) );
  p.drawText(p1, gate->name() );

  
  //Upper left handle
  handles.append(new GateHandle_1(p1));

  //Lower right
  handles.append(new GateHandle_2(p2));

 }
}


