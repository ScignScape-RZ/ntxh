
// // license___here

#include "ViewWidget.h"
#include "ViewSettings.h"

#include "tool/ViewToolChoice.h"
#include "tool/ViewTool.h"

#include "gate/GateHandle.h"
#include "gates/GateSet.h"
#include "gates/gate-info.h"


#include "data/Dataset.h"
#include "data/ChannelInfo.h"


#include "FacsanaduProject.h"
#include "MainWindow.h"

#include <limits>


#include <QImage>
#include <QPainter>


// package facsanadu.gui.view;


ViewWidget::ViewWidget(MainWindow* mw)
{
 //Dataset dataset;

 // setchans_; // = new LinkedList<Callback*>();
 //ViewTool tool_ ;

 trans_ = new ViewTransform();
 viewsettings_ = new ViewSettings();

 // handles_ = new LinkedList<GateHandle>();

 curhandle_ = nullptr;

 // pointLast_; // = new QPointF();
 maxevents_ = 0; //? 

 mainWindow_ = mw;

 lastGatingTime_ = 0;
 img_ = nullptr;


 setMouseTracking(true);
 setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
 setTool(ViewToolChoice::SELECT);
}

void ViewWidget::setDataset(Dataset* ds)
{
 dataset_ = ds;
}

void ViewWidget::render()
{
 update();
}


void ViewWidget::updatePointImage()
{
  //?FacsanaduProject* project = mainWindow_->project();
  //?GatingResult* gr = project->get_GatingResult(dataset_);  

  // // GatingResult not yet impl ...
 long newGatingTime = 0; //gr->lastGatingCalculationTime();

// System.out.println("last view "+lastGatingTime+"   last g "+newGatingTime+ "    "+(lastGatingTime<newGatingTime));

 if(img_ == nullptr || lastGatingTime_ < newGatingTime 
   || img_->width() != width() || img_->height() != height())
 {
/*
  System.out.println("update cache");
  img= QImage(width(), height(), Format.Format_RGB32);
  QPainter pm2=new QPainter(img);
  pm2.setBrush(new QBrush(QColor.white));
  pm2.drawRect(-5,-5,10000,10000);
  ViewRenderer.renderData(viewsettings, dataset, gr, trans, pm2, maxevents); 
pm2.end();
  lastGatingTime=newGatingTime;
*/
 }
}

void ViewWidget::paintEvent(QPaintEvent* pe)
{
 QWidget::paintEvent(pe);
  //? super.paintEvent(pe);
  //? FacsanaduProject* project = mainWindow_->project();

  //? GatingResult* gr = project->get_GatingResult(dataset_);

 trans_->setTotalHeight(contentsRect().height());
 trans_->setTotalWidth(contentsRect().width());
 trans_->set_viewsettings(viewsettings_);

 LinkedList<GateHandle*> handles; // =new LinkedList<GateHandle>();
 QPainter pm; //=new QPainter(this);

 updatePointImage();

 pm.drawImage(QPoint {0, 0}, *img_);

/*
 ViewRenderer.renderGates(viewsettings, dataset, gr, trans, pm, handles, maxevents); 

 //Now render handles?
 for(GateHandle h:handles)
 {
  pm.setBrush(new QBrush(QColor.transparent));
  pm.setPen(QColor.red);

  int size = 2;
  pm.drawRect(new QRectF(h.getX()-size, h.getY()-size,2*size,2*size));
 }
*/

 pm.end();
}


GateHandle* ViewWidget::getClosestHandle(const QPointF& pos, double cutoff)
{
 if(!tool_->allowHandle())
   return nullptr;

 GateHandle* ch = nullptr;

 double cd = std::numeric_limits<double>::max();

 for(GateHandle* h : handles_)
 {
  double dx = pos.x() - h->getX();
  double dy = pos.y() - h->getY();
  double d2 = (dx * dx) + (dy * dy);
  if(d2 < cd)
  {
   cd = d2;
   ch = h;
  }
 }
 if(cd < (cutoff * cutoff))
   return ch;
 else
   return nullptr;
}

void ViewWidget::mousePressEvent(QMouseEvent* event)
{
 pointLast_ = event->localPos(); //posF();

  // super.mousePressEvent(event);
 QWidget::mousePressEvent(event);

 if(event->buttons() == Qt::LeftButton)
 {
  curhandle_ = nullptr;
  GateHandle* handle = getClosestHandle(event->localPos(), 10);
  if(handle != nullptr)
  {
   //Move a handle
   curhandle_ = handle; 
  }
  else if(mousePosInBoundary(event->pos()))
  {
   setchans_.clear();
   FacsanaduProject* project = mainWindow_->project();
   int invy = height() - event->pos().y();
   QMenu* menu = new QMenu();

   //Menu to set axis, and histogram
   QMenu* menuAxis = menu->addMenu(tr("Set axis"));
   QMenu* menuHist = new QMenu(tr("Set histogram"));
   bool lastwasx = true;
   if(event->pos().x()>invy)
     lastwasx=true;
   else
     lastwasx=false;

   menu->addAction(tr("Swap axis"), this, "actionSwapAxis()");


   QList<ChannelInfo*> chans = dataset_->getChannelInfo();

   for(int i=0; i < chans.size(); i++)
   {
    ChannelInfo* ci = chans.at(i);
    CallbackSetChannel* set = new CallbackSetChannel();
    set->chanid = i;
    set->forx = lastwasx;
    menuAxis->addAction(ci->formatName(), set, &CallbackSetChannel::actionSet); 
      //this //&set
      //, Q_SLOT("actionSet()") );
    setchans_.append(set);

    CallbackSetHistogram* sethist = new CallbackSetHistogram();
    sethist->chanid = i;
    menuHist->addAction(ci->formatName(), sethist,
      &CallbackSetHistogram::actionSet);
      //sethist, "actionSet()");
    setchans_.append(sethist);
   }

   //Menu to set source population
   QMenu* mSetSource = menu->addMenu(tr("Set source population"));
   for(Gate* g : project->gateset()->getGates())
   {
    CallbackSetGate* sg = new CallbackSetGate();
    sg->g = g;
    setchans_.append(sg);
      // 
    mSetSource->addAction("g->name", sg, &CallbackSetGate::actionSet); 
     //sg, "actionSet()");
   } 

   //Menu to set scaling
   QMenu* mSetScaling = menu->addMenu(tr("Set zoom"));
   for(double d : QList<double> {0.1,0.5,1,2,5,10,20,50})
   {
    CallbackSetZoom* sg = new CallbackSetZoom();
    sg->scale = d;
    sg->isx = lastwasx;
    setchans_.append(sg);
    mSetScaling->addAction(QString::number(d), sg, &CallbackSetZoom::actionSet); 
      //"actionSet()");
   } 

   QMenu* menuTrans = menu->addMenu(tr("Set transform"));

   CallbackSetTransformation* tLin = new CallbackSetTransformation
     ( "Linear" , //TransformationType::LINEAR, 
      lastwasx); 
   CallbackSetTransformation* tLog = new CallbackSetTransformation
     (  "Log" ,  // TransformationType::LOG,
      lastwasx);


   menuTrans->addAction("Linear", tLin, &CallbackSetTransformation::actionSet);
      // tlin, "actionSet()");

   menuTrans->addAction("Log", tLog, &CallbackSetTransformation::actionSet); 
      // tLog, "actionSet()");


   QMenu* mHistBins = new QMenu(tr("Set histogram bins"));

   for(int d : QList<int>{5,10,15,20,30,40,50,100,200,300})
   {
    CallbackSetBins* sg = new CallbackSetBins();
    sg->bins=d;
    setchans_.append(sg);
    mHistBins->addAction(QString::number(d), sg, &CallbackSetBins::actionSet); 
      //sg, "actionSet()");
   }

   menu->addSeparator();
   menu->addMenu(menuHist);
   menu->addMenu(mHistBins);
   menu->exec(event->globalPos());
  }
  else
  {
   tool_->mousePressEvent(event);
  }
 }
}

void ViewWidget::mouseDoubleClickEvent(QMouseEvent* e)
{
  //super.mouseDoubleClickEvent(e);
 QWidget::mouseDoubleClickEvent(e);
 tool_->mouseDoubleClickEvent(e);
}

void ViewWidget::mouseReleaseEvent(QMouseEvent* ev)
{
  //super.mouseReleaseEvent(ev);
 QWidget::mouseReleaseEvent(ev);
 curhandle_ = nullptr;
 tool_->mouseReleaseEvent(ev);
 
  //? mainWindow_->handleEvent(EventGatesChanged());
}


void ViewWidget::mouseMoveEvent(QMouseEvent* event)
{
 QWidget::mouseMoveEvent(event);
 
 if(curhandle_ != nullptr)
 {
  QPointF p = trans_->mapScreenToFcs(event->localPos());
  curhandle_->move2(mainWindow_, p.x(), p.y());
 }
 else
   tool_->mouseMoveEvent(event);

 pointLast_ = event->localPos();
}


bool ViewWidget::mousePosInBoundary(const QPoint& pos)
{
 int invy = height() - pos.y();
 return ( pos.x() < trans_->graphOffsetXY() ) 
  || ( invy < trans_->graphOffsetXY() );
}

void ViewWidget::setChannels(int indexX, int indexY)
{
 viewsettings_->set_indexX(indexX);
 viewsettings_->set_indexY(indexY);
}

void ViewWidget::setSettings(ViewSettings* vs)
{
 viewsettings_ = vs;
}

//interface Callback
//{
// void actionSet();
//}

// // Callback: Set channel

void ViewWidget::CallbackSetChannel::actionSet()
{
 if(forx)
   vw->viewsettings_->set_indexX(chanid);
 
 else
   vw->viewsettings_->set_indexY(chanid);

 vw->mainWindow_->handleEvent(EventViewsChanged());
}


void ViewWidget::CallbackSetHistogram::actionSet()
{
 vw->viewsettings_->setHistogram(chanid);
 vw->mainWindow_->handleEvent(EventViewsChanged());
}


void ViewWidget::CallbackSetGate::actionSet()
{
 vw->viewsettings_->set_gate(g);
 vw->mainWindow_->handleEvent(EventViewsChanged());
}

ViewWidget::CallbackSetTransformation::CallbackSetTransformation(
  QString tt, // TransformationType t, 
  bool forx)
{
 ttype = tt;
 forx = forx;
}

void ViewWidget::CallbackSetTransformation::actionSet()
{
 int index;

 if(forx)
   index=vw->viewsettings_->indexX();
 else
   index=vw->viewsettings_->indexY();

 Q_UNUSED(index)

/*
 Transformation trans = nullptr;
 if(t == TransformationType.LOG)
   trans_ = new TransformationLog();
 if(t==TransformationType.LINEAR)
   viewsettings.transformation.set(index, trans);
 else if(t==TransformationType.LOG)
   viewsettings.transformation.set(index, trans);
*/

 vw->mainWindow_->handleEvent(EventViewsChanged());
}

void ViewWidget::CallbackSetZoom::actionSet()
{
 if(isx)
   vw->viewsettings_->set_zoomX(scale);
 else
   vw->viewsettings_->set_zoomY(scale);

 vw->mainWindow_->handleEvent(new EventViewsChanged());
}

void ViewWidget::CallbackSetBins::actionSet()
{
 vw->viewsettings_->set_numHistBins(bins);
 vw->mainWindow_->handleEvent(EventViewsChanged());
}

int ViewWidget::getIndexX()
{
 return viewsettings_->indexX();
}

int ViewWidget::getIndexY()
{
 return viewsettings_->indexY();
}

void ViewWidget::sendEvent(FacsanaduEvent event)
{
 mainWindow_->handleEvent(event);
}

void ViewWidget::actionSwapAxis()
{
 viewsettings_->swapAxis();
 mainWindow_->handleEvent(EventViewsChanged());
}

void ViewWidget::setTool(ViewToolChoice::Enum e)
{
 tool_ = ViewToolChoice::getTool(this, e);
}

void ViewWidget::addGate(Gate* g)
{
 mainWindow_->addGate(viewsettings_->gate(), g);
}

void ViewWidget::invalidateCache()
{
 img_ = nullptr;
}

