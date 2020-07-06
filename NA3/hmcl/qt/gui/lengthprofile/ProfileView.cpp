
// // license___here

#include "ProfileView.h"


// package facsanadu.gui.lengthprofile;


ProfileView::ProfileView(MainWindow* mw)
{
 mw_ = mw;
 setMouseTracking(true);
}
 
void ProfileView::paintEvent(QPaintEvent e)
  {
  super.paintEvent(e);
  QPainter pm=new QPainter(this);
  pm.fillRect(new QRect(0, 0,width(),height()), new QBrush(QColor.fromRgb(255,255,255)));
  
  ArrayList<QColor> colors=new ArrayList<QColor>();
  colors.add(QColor.fromRgb(0,0,0));
  colors.add(QColor.fromRgb(255,0,0));
  colors.add(QColor.fromRgb(0,255,0));
  colors.add(QColor.fromRgb(0,0,255));
  
  int h=height();
  for(int eventid:this.eventid)
   if(ds!=null && eventid>=0 && eventid<ds.getNumObservations())
    {
    for(int profid=0;profid<ds.lengthprofsInfo.size();profid++)
     if(showchan.get(profid))
      {
      //LengthProfile prof=ds.lengthprofsInfo.get(profid);
      LengthProfileData data=ds.lengthprofsData.get(eventid);
      double scaleY=scale.get(profid)*h;
      
      QPen pen=new QPen(colors.get(profid));
      pm.setPen(pen);
      
      int len=data.getLength();
      QPainterPath path=new QPainterPath();
      for(int i=0;i<len;i++)
       {
       double x;
       if(normalizeLength)
        x=i*width()/data.getLength();
       else
        x=i*width()/1050; //what is the maximum length in the set? could be stored in the info
       
       double y=h-1-data.data[profid][i]*scaleY;
       if(i==0)
        path.moveTo(x,y);
       else
        path.lineTo(x,y);
       }
      pm.drawPath(path);
      }
    }
  
  //Draw profile channel
  if(curchannel!=null)
   {
   QPen pen=new QPen(colors.get(curchannel.channel));
   pen.setWidth(2);
   pm.setPen(pen);

   int x1=toViewX(curchannel.from);
   int x2=toViewX(curchannel.to);
   
   pm.drawLine(x1, 3, x1, height());
   pm.drawLine(x2, 3, x2, height());   
   pen.setWidth(0);
   pm.drawLine(x1, 3, x2, 3);
//   pm.drawLine(x1, height()-1, x2, height()-1);
   }
  
  pm.end();
  }

int ProfileView::toViewX(int x)
{
  return x*width()/1050;
}

int ProfileView::fromViewX(int x)
{
  return x*1050/width();
}

void ProfileView::setevent(Dataset ds, int i)
  {
  setevent(ds, Arrays.asList(i));
  }

void ProfileView::setevent(Dataset ds, List<Integer> ids)
  {
  this.ds=ds;
  eventid.clear();
  eventid.addAll(ids);
  update();
  }

 void ProfileView::mousePressEvent(QMouseEvent event)
  {
  pointLast=event.posF();
  super.mousePressEvent(event);
  if(event.button()==MouseButton.LeftButton)
   {
   moveBoundary=-1;
   if(curchannel!=null)
    {
    int[] x=new int[]{
      toViewX(curchannel.from),
      toViewX(curchannel.to)};
    int si=-1;
    int smallest=100000;
    for(int i=0;i<x.length;i++)
     {
     int dx=Math.abs(event.x()-x[i]);
     if(si==-1 || dx<smallest)
      {
      smallest=dx;
      si=i;
      }
     }
    if(smallest<30)
     {
     //Close enough
     moveBoundary=si;
     }
    }
   }
  
  }
 
 void ProfileView::mouseDoubleClickEvent(QMouseEvent e)
  {
  super.mouseDoubleClickEvent(e);
  }
 
void ProfileView::mouseReleaseEvent(QMouseEvent ev)
  {
  super.mouseReleaseEvent(ev);
  if(curchannel!=null && moveBoundary!=-1)
   {
   //Recompute channels
   mw.recalcProfChan(curchannel);
   }
  moveBoundary=-1;
  //mw.handleEvent(new EventGatesMoved());   //TODO something like this!
  }

int ProfileView::clamp(int x, int from, int to)
  {
  if(x<from)
   return from;
  else if(x>to)
   return to;
  else
   return x;
  }
 
void ProfileView::mouseMoveEvent(QMouseEvent event)
{
 super.mouseMoveEvent(event);
  
 if(moveBoundary!=-1 && curchannel!=null)
 {

  int newx=fromViewX(event.pos().x());
  if(moveBoundary==0)
    curchannel.from=clamp(newx,0,curchannel.to-1);
  else if(moveBoundary==1)
    curchannel.to=clamp(newx,curchannel.from+1,1050);
  update();
 }
 pointLast=event.posF();
}

