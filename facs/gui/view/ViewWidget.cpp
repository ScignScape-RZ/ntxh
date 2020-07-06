
// // license___here

#include "ViewWidget.h"


// package facsanadu.gui.view;



ViewWidget::ViewWidget(MainWindow* mw)
{
 //Dataset dataset;

 setchans_ = new LinkedList<Callback>();
 //ViewTool tool_ ;

 trans_ = new ViewTransform();
 viewsettings_ = new ViewSettings();

 handles_ = new LinkedList<GateHandle>();

 curhandle_ = nullptr;

 pointLast_ = new QPointF();
 int maxevents;

 mainWindow_ = mw;

 long lastGatingTime_ = 0;
 img_ = nullptr;


 setMouseTracking(true);
 setSizePolicy(Policy.Expanding, Policy.Expanding);
 setTool(ViewToolChoice.SELECT);
}

void ViewWidget::setDataset(Dataset ds)
{
 dataset_ = ds;
}

void ViewWidget::render()
{
 update();
}


void ViewWidget::updatePointImage()
{
 FacsanaduProject project=mainWindow.project;
 GatingResult gr=project.gatingResult.get(dataset);
 long newGatingTime=gr.lastGatingCalculationTime();
 System.out.println("last view "+lastGatingTime+"   last g "+newGatingTime+ "    "+(lastGatingTime<newGatingTime));
 if(img==null || lastGatingTime<newGatingTime || img.width()!=width() || img.height()!=height())
 {
  System.out.println("update cache");
  img=new QImage(width(),height(), Format.Format_RGB32);
  QPainter pm2=new QPainter(img);
  pm2.setBrush(new QBrush(QColor.white));
  pm2.drawRect(-5,-5,10000,10000);
  ViewRenderer.renderData(viewsettings, dataset, gr, trans, pm2, maxevents); 
pm2.end();
  lastGatingTime=newGatingTime;
 }
}

void ViewWidget::paintEvent(QPaintEvent pe)
{
 super.paintEvent(pe);
 FacsanaduProject project=mainWindow.project;
 GatingResult gr=project.gatingResult.get(dataset);

 trans.setTotalHeight(contentsRect().height());
 trans.setTotalWidth(contentsRect().width());
 trans.viewsettings=viewsettings;

 handles=new LinkedList<GateHandle>();
 QPainter pm=new QPainter(this);

 updatePointImage();
 pm.drawImage(new QPoint(0,0), img);


 ViewRenderer.renderGates(viewsettings, dataset, gr, trans, pm, handles, maxevents); 

 //Now render handles?
 for(GateHandle h:handles)
 {
  pm.setBrush(new QBrush(QColor.transparent));
  pm.setPen(QColor.red);

  int size=2;
  pm.drawRect(new QRectF(h.getX()-size, h.getY()-size,2*size,2*size));
 }

 pm.end();
}


GateHandle ViewWidget::getClosestHandle(QPointF pos, double cutoff)
{
 if(!tool.allowHandle())
   return null;
 GateHandle ch=null;
 double cd=Double.MAX_VALUE;
 for(GateHandle h:handles)
 {
  double dx=pos.x()-h.getX();
  double dy=pos.y()-h.getY();
  double d2=dx*dx + dy*dy;
  if(d2<cd)
  {
   cd=d2;
   ch=h;
  }
 }
 if(cd<cutoff*cutoff)
   return ch;
 else
   return null;
}

void ViewWidget::mousePressEvent(QMouseEvent event)
{
 pointLast=event.posF();
 super.mousePressEvent(event);
 if(event.button()==MouseButton.LeftButton)
 {
  curhandle=null;
  GateHandle handle=getClosestHandle(event.posF(), 10);
  if(handle!=null)
  {
   //Move a handle
   curhandle=handle; 
  }
  else if(mousePosInBoundary(event.pos()))
  {
   setchans.clear();
   FacsanaduProject proj=mainWindow.project;
   int invy=height()-event.pos().y();
   QMenu menu=new QMenu();

   //Menu to set axis, and histogram
   QMenu menuAxis=menu.addMenu(tr("Set axis"));
   QMenu menuHist=new QMenu(tr("Set histogram"));
   bool lastwasx=true;
   if(event.pos().x()>invy)
     lastwasx=true;
   else
     lastwasx=false;

   menu.addAction(tr("Swap axis"),this,"actionSwapAxis()");


   ArrayList<ChannelInfo> chans=dataset.getChannelInfo();
   for(int i=0;i<chans.size();i++)
   {
    ChannelInfo ci=chans.get(i);
    CallbackSetChannel set=new CallbackSetChannel();
    set.chanid=i;
    set.forx=lastwasx;
    menuAxis.addAction(ci.formatName(), set, "actionSet()");
    setchans.add(set);

    CallbackSetHistogram sethist=new CallbackSetHistogram();
    sethist.chanid=i;
    menuHist.addAction(ci.formatName(), sethist, "actionSet()");
    setchans.add(sethist);
   }

   //Menu to set source population
   QMenu mSetSource=menu.addMenu(tr("Set source population"));
   for(Gate g:proj.gateset.getGates())
   {
    CallbackSetGate sg=new CallbackSetGate();
    sg.g=g;
    setchans.add(sg);
    mSetSource.addAction(g.name, sg, "actionSet()");
   } 

   //Menu to set scaling
   QMenu mSetScaling=menu.addMenu(tr("Set zoom"));
   for(double d:new double[]{0.1,0.5,1,2,5,10,20,50})
   {
    CallbackSetZoom sg=new CallbackSetZoom();
    sg.scale=d;
    sg.isx=lastwasx;
    setchans.add(sg);
    mSetScaling.addAction(""+d, sg, "actionSet()");
   } 

   QMenu menuTrans = menu.addMenu(tr("Set transform"));
   CallbackSetTransformation tLin=new CallbackSetTransformation (TransformationType.LINEAR, lastwasx); 
   CallbackSetTransformation tLog=new CallbackSetTransformation(TransformationType.LOG, lastwasx);
   menuTrans.addAction("Linear", tLin, "actionSet()");
   menuTrans.addAction("Log", tLog, "actionSet()");


   QMenu mHistBins=new QMenu(tr("Set histogram bins"));
   for(int d:new int[]{5,10,15,20,30,40,50,100,200,300})
   {
    CallbackSetBins sg=new CallbackSetBins();
    sg.bins=d;
    setchans.add(sg);
    mHistBins.addAction(""+d, sg, "actionSet()");
   }
   menu.addSeparator();
   menu.addMenu(menuHist);
   menu.addMenu(mHistBins);
   menu.exec(event.globalPos());
  }
  else
  {
   tool.mousePressEvent(event);
  }
 }
}

void ViewWidget::mouseDoubleClickEvent(QMouseEvent e)
{
 super.mouseDoubleClickEvent(e);
 tool.mouseDoubleClickEvent(e);
}

void ViewWidget::mouseReleaseEvent(QMouseEvent ev)
{
 super.mouseReleaseEvent(ev);
 curhandle=null;
 tool.mouseReleaseEvent(ev);
 mainWindow.handleEvent(new EventGatesChanged());
}


void ViewWidget::mouseMoveEvent(QMouseEvent event)
{
 super.mouseMoveEvent(event);
 if(curhandle!=null)
 {
  QPointF p=trans.mapScreenToFcs(event.posF());
  curhandle.move2(mainWindow, p.x(), p.y());
 }
 else
   tool.mouseMoveEvent(event);
 pointLast_ = event.posF();
}


bool ViewWidget::mousePosInBoundary(QPoint pos)
{
 int invy=height()-pos.y();
 return pos.x() < trans.graphOffsetXY || invy < trans.graphOffsetXY;
}

void ViewWidget::setChannels(int indexX, int indexY)
{
 viewsettings.indexX=indexX;
 viewsettings.indexY=indexY;
}

void ViewWidget::setSettings(ViewSettings vs)
{
 viewsettings=vs;
}

//interface Callback
//{
// void actionSet();
//}

// // Callback: Set channel

void ViewWidget::CallbackSetChannel::actionSet()
{
 if(forx)
   viewsettings.indexX=chanid;
 else
   viewsettings.indexY=chanid;
 mainWindow.handleEvent(new EventViewsChanged());
}


void ViewWidget::CallbackSetHistogram::actionSet()
{
 viewsettings.setHistogram(chanid);
 mainWindow.handleEvent(new EventViewsChanged());
}


void ViewWidget::CallbackSetGate::actionSet()
{
 viewsettings.gate=g;
 mainWindow.handleEvent(new EventViewsChanged());
}

void ViewWidget::CallbackSetTransformation::CallbackSetTransformation(TransformationType t, boolean forx)
{
 t_ = t;
 forx_ = forx;
}

void ViewWidget::CallbackSetTransformation::actionSet()
{
 int index;
 if(forx)
   index=viewsettings.indexX;
 else
   index=viewsettings.indexY;
 Transformation trans=null;
 if(t==TransformationType.LOG)
   trans=new TransformationLog();
 if(t==TransformationType.LINEAR)
   viewsettings.transformation.set(index, trans);
 else if(t==TransformationType.LOG)
   viewsettings.transformation.set(index, trans);
 mainWindow.handleEvent(new EventViewsChanged());
}

void ViewWidget::CallbackSetZoom::actionSet()
{
 if(isx)
   viewsettings.zoomX=scale;
 else
   viewsettings.zoomY=scale;
 mainWindow.handleEvent(new EventViewsChanged());
}

void ViewWidget::CallbackSetBins::actionSet()
{
 viewsettings.numHistBins=bins;
 mainWindow.handleEvent(new EventViewsChanged());
}

int ViewWidget::getIndexX()
{
 return viewsettings.indexX;
}

int ViewWidget::getIndexY()
{
 return viewsettings.indexY;
}

void ViewWidget::sendEvent(FacsanaduEvent event)
{
 mainWindow.handleEvent(event);
}

void ViewWidget::actionSwapAxis()
{
 viewsettings.swapAxis();
 mainWindow.handleEvent(new EventViewsChanged());
}

void ViewWidget::setTool(ViewToolChoice t)
{
 tool=ViewToolChoice.getTool(this, t);
}

void ViewWidget::addGate(Gate g)
{
 mainWindow.addGate(viewsettings.gate, g);
}

void ViewWidget::invalidateCache()
{
 img=null;
}

