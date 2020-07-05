// package facsanadu.gui.view;

// //

class ViewWidget : QWidget
{
 Dataset dataset_;
 LinkedList<Callback> setchans_; // = new LinkedList<Callback>();
 ViewTool tool_;

 LinkedList<GateHandle> handles_; //=new LinkedList<GateHandle>();
 
 GateHandle curhandle_; //=null;
 
 QPointF pointLast_; // =new QPointF();

 long lastGatingTime=0;
 QImage* img = nullptr;
 void updatePointImage();

 bool mousePosInBoundary(QPoint pos);


protected:

 void paintEvent(QPaintEvent pe) Q_DECLARE_OVERRIDE;
 void mousePressEvent(QMouseEvent event) Q_DECLARE_OVERRIDE;
 void mouseDoubleClickEvent(QMouseEvent e) Q_DECLARE_OVERRIDE;
 void mouseReleaseEvent(QMouseEvent ev) Q_DECLARE_OVERRIDE;
 void mouseMoveEvent(QMouseEvent event) Q_DECLARE_OVERRIDE;


public:

 MainWindow mainWindow;
 ViewTransform trans=new ViewTransform();
 ViewSettings viewsettings=new ViewSettings();
 int maxevents;

 ViewWidget(MainWindow mw);
 void setDataset(Dataset ds)
 void render()
 
 GateHandle getClosestHandle(QPointF pos, double cutoff)
 
 void setChannels(int indexX, int indexY);

 void setSettings(ViewSettings vs);

// interface Callback
//  {
//  void actionSet();
//  }

 class Callback
 {
  void actionSet();
 };

 // //
 class CallbackSetChannel //implements Callback
 {
  boolean forx;
  int chanid;
  void actionSet();
 };

 // // Callback: Set histogram
 class CallbackSetHistogram // implements Callback
 {
  int chanid;
  void actionSet();
 };
 
 // // Callback: set displayed gate
 class CallbackSetGate //implements Callback
 {
  Gate g;
  void actionSet();
 };

 // // Callback: set transformation
 class CallbackSetTransformation //implements Callback
 {
  TransformationType t;
  bool forx;
  
  CallbackSetTransformation(TransformationType t, boolean forx);
  
  void actionSet();
 };

 
 class CallbackSetZoom //implements Callback
 {
  double scale;
  boolean isx;
  void actionSet();
 };

 class CallbackSetBins // implements Callback
 {
  int bins;
  void actionSet();
 }
 
 int getIndexX();
 int getIndexY();
 void sendEvent(FacsanaduEvent event);

 void actionSwapAxis();

 void setTool(ViewToolChoice t);

 void addGate(Gate g);

 void invalidateCache();

};


