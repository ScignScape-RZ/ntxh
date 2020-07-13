
// // license___here_h


#ifndef ViewWidget__H
#define ViewWidget__H


#include <QPointF>
#include <QImage>
#include <QPaintEvent>
#include <QMouseEvent>

#include <QWidget>
#include <QPointF>
#include <QImage>

#include "../events/FacsanaduEvent.h"

#include "ViewTransform.h"
#include "tool/ViewToolChoice.h"



// // temp
#include<QList>
#define LinkedList QList

// package facsanadu.gui.view;

// //

class Dataset;
class GateHandle; 
class ViewTool;
class MainWindow;
class ViewTransform;
class ViewSettings;
class Gate;
class TransformationType;


class ViewWidget : public QWidget
{
public:
 class Callback;

private:

 Dataset* dataset_;
 LinkedList<Callback*> setchans_; // = new LinkedList<Callback>();
 ViewTool* tool_;

 LinkedList<GateHandle*> handles_; //=new LinkedList<GateHandle>();
 
 GateHandle* curhandle_; //=null;
 
 QPointF pointLast_; // =new QPointF();

 long lastGatingTime_;  // =0;
 QImage* img_; // = nullptr;
 void updatePointImage();

 bool mousePosInBoundary(const QPoint& pos);


protected:

 void paintEvent(QPaintEvent* pe)  Q_DECL_OVERRIDE;
 void mousePressEvent(QMouseEvent* event)  Q_DECL_OVERRIDE;
 void mouseDoubleClickEvent(QMouseEvent* e)  Q_DECL_OVERRIDE;
 void mouseReleaseEvent(QMouseEvent* ev)  Q_DECL_OVERRIDE;
 void mouseMoveEvent(QMouseEvent* event)  Q_DECL_OVERRIDE;


public:

 MainWindow* mainWindow_;
 ViewTransform* trans_; // =new ViewTransform();
 ViewSettings* viewsettings_; // =new ViewSettings();
 int maxevents_;

 ViewWidget(MainWindow* mw);
 void setDataset(Dataset* ds);
 void render();
 
 GateHandle* getClosestHandle(const QPointF& pos, double cutoff);
 
 void setChannels(int indexX, int indexY);

 void setSettings(ViewSettings* vs);

// interface Callback
//  {
//  void actionSet();
//  }

//*
 class Callback : public QObject
 {
//  Q_OBJECT
 public:

  ViewWidget* vw;
  virtual void actionSet();
 };
//*/

 // //
 class CallbackSetChannel : public Callback  //implements Callback
 {
//  Q_OBJECT

 public:
  bool forx;
  int chanid;
  void actionSet() Q_DECL_OVERRIDE;
 };

 // // Callback: Set histogram
 class CallbackSetHistogram : public Callback // implements Callback
 {
 public:
  int chanid;
  void actionSet() Q_DECL_OVERRIDE;
 };

 // // Callback: set displayed gate
 class CallbackSetGate : public Callback // implements Callback
 {
 public:
  Gate* g;
  void actionSet() Q_DECL_OVERRIDE;
 };

 // // Callback: set transformation
 class CallbackSetTransformation : public Callback //implements Callback
 {
 public:
  QString ttype;  // TransformationType* t;
  bool forx;
  
  CallbackSetTransformation(QString ttype, // TransformationType* t, 
    bool forx);
  
  void actionSet() Q_DECL_OVERRIDE;
 };

 
 class CallbackSetZoom : public Callback //implements Callback
 {
 public:
  double scale;
  bool isx;
  void actionSet() Q_DECL_OVERRIDE;
 };

 class CallbackSetBins : public Callback  // implements Callback
 {
 public:
  int bins;
  void actionSet() Q_DECL_OVERRIDE;
 };
 
 int getIndexX();
 int getIndexY();
 void sendEvent(FacsanaduEvent event);

 void actionSwapAxis();

 void setTool(ViewToolChoice::Enum e);

 void addGate(Gate* g);

 void invalidateCache();

};

#endif // __H
 



