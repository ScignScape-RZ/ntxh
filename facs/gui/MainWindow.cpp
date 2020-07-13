// // license___here

#include "MainWindow.h"

#include "GatesListWidget.h"
#include "ProfileChannelWidget.h"
#include "ViewsListWidget.h"
#include "DatasetListWidget.h"
#include "panes/CompensationPane.h"
#include "panes/DatasetInfoPane.h"
#include "FacsanaduProject.h"

#include "resource/ImgResource.h"

#include "panes/ViewsPane.h"
#include "panes/GateStatsPane.h"
#include "lengthprofile/ProfilePane.h"

#include "DialogAbout.h"

#include "GraphExportWindow.h"

#include "view/GraphExporter.h"

#include "../data/ExportFcsToCSV.h"
#include "../data/Dataset.h"


#include "QtProgramInfo.h"

#include <QMenu>
#include <QMimeData>
#include <QFile>
#include <QFileDialog>
#include <QMutex>
#include <QMutexLocker>
#include <QInputDialog>

#include <QApplication>

#include <QDesktopServices>

#include <functional>

//#ifdef HIDE

struct Facs_IOException {};
struct Facs_RuntimeException {};
struct Facs_Exception {};

std::function<QList<Dataset*>()> do_MainWindow_GateCalcThread_getCurrentDatasets;

QList<Dataset*> _MainWindow_GateCalcThread::getCurrentDatasets()
{
 return do_MainWindow_GateCalcThread_getCurrentDatasets();
 // synchronized (selDatasetsCache)
 // {

//? QMutexLocker lock(&selDatasetsCache_mutex_);
//? QList<Dataset*> d (selDatasetsCache_);
//? return d;
 //? 

// return {};
};


#define connect_this(x, y, z) connect(y, &x, \
   this, &MainWindow::z);

MainWindow::MainWindow()
{
 tabwidget_ = new QTabWidget();
 menubar_ = new QMenuBar();

 gatesw_ = new GatesListWidget(this);
 pc_ = new ProfileChannelWidget(this);
 viewsw_ = new ViewsListWidget(this);
 datasetsw_ = new DatasetListWidget(this);
 paneCompensation_ = new CompensationPane(this);
 paneMetadata_ = new DatasetInfoPane(this);

 project_ = new FacsanaduProject();

 calcthread_ = new _MainWindow_GateCalcThread(project_);

 connect( (_MainWindow_GateCalcThread*) calcthread_,
   &_MainWindow_GateCalcThread::callbackDoneCalc_signal, 
   [this](Dataset*)
  {
   updateall();
  });
 
 do_MainWindow_GateCalcThread_getCurrentDatasets = [this]()
  {
   QMutexLocker lock(&this->selDatasetsCache_mutex_);
   QList<Dataset*> d (this->selDatasetsCache_);
   return d;
  };

// paneViews_;
// paneStats_;
// paneProfile_;
 
//? currentProjectFile_ = ; //nullptr;

 lastDirectory_ = QDir(".");
 
 isUpdating_ = false;

 setMenuBar(menubar_);

 ImgResource::setWindowIcon(this);
 
 paneViews_ = new ViewsPane(this);
 paneStats_ = new GateStatsPane(this);
 paneProfile_ = new ProfilePane(this);
 pc_->set_paneProfile(paneProfile_);
 
 QMenu* mFile = menubar_->addMenu(tr("File"));
 mFile->addAction(tr("New project"), this, "actionNewProject()");
 mFile->addAction(tr("Open project"), this, "actionOpenProject()");
 mFile->addAction(tr("Save project"), this, "actionSaveProject()");
 mFile->addAction(tr("Save project as"), this, "actionSaveProjectAs()");
 mFile->addSeparator();
 mFile->addAction(tr("Exit"), this, "close()");

 
 QMenu* mExport = menubar_->addMenu(tr("Export"));
 mExport->addAction(tr("Graphs"), this, "actionExportGraphs()");
 mExport->addAction(tr("Statistics"), this, "actionExportStatistics()");
 mExport->addAction(tr("Dataset as CSV"), this, "actionExportCSV()");

 QMenu* mSettings = menubar_->addMenu(tr("Settings"));
 mSettings->addAction(tr("Set number of CPU cores"), this, "actionSetNumCores()");
 menubar_->addSeparator();
 
 QMenu* mHelp = menubar_->addMenu(tr("Help"));
 mHelp->addAction(tr("About"), this, "actionAbout()");
 mHelp->addAction(tr("Website"), this, "actionWebsite()");

 //? datasetsw.selectionChanged.connect(this,"actionDsChanged()");
 
 connect_this(DatasetListWidget ::selectionChanged ,datasetsw_ ,actionDsChanged) 

 QVBoxLayout* layLeft = new QVBoxLayout();

 layLeft->addWidget(datasetsw_);
 layLeft->addWidget(viewsw_);
 layLeft->addWidget(gatesw_);
 layLeft->addWidget(pc_);
//? layLeft->addLayout(datasetsw_);
//? layLeft->addLayout(viewsw_);
//? layLeft->addLayout(gatesw_);
//? layLeft->addLayout(pc_);



//? viewsw.actionNewView();

 
 /// Load all files from directory
/*
 try
 {
  File getfrom=new File("/home/mahogny/javaproj/quickfacs/test4");
  if(getfrom.exists())
  for(File path:getfrom.listFiles())
   if(path.getName().endsWith(".fcs") || path.getName().endsWith(".dat"))
   loadFile(path);
  }
 catch (IOException e)
  {
  e.printStackTrace();
  }
 //loadFile(new File("/ztuff/ztufffromvenus/ztuff/customer/jin/rpt-5/rp5-larva-PMT530-day8-2010-09-11.txt"));
 */

 tabwidget_->addTab(paneViews_, tr("Graphs"));
 tabwidget_->addTab(paneStats_, tr("Statistics"));
 tabwidget_->addTab(paneProfile_, tr("Length profiles"));
 tabwidget_->addTab(paneCompensation_, tr("Compensation"));
 tabwidget_->addTab(paneMetadata_, tr("Dataset info"));

 QHBoxLayout* lay = new QHBoxLayout();
 lay->addLayout(layLeft);
 lay->addWidget(tabwidget_);
 
 QWidget* cent = new QWidget();
 cent->setLayout(lay);
 setCentralWidget(cent);

 
 updateall();
 setAcceptDrops(true);
 adjustSize();
 resize(1000, size().height());
 show();
}

 
void MainWindow::updateall()
{
 bool wasUpdating = isUpdating_;
 isUpdating_ = true;
 viewsw_->updateViewsList();
 gatesw_->updateGatesList();
 datasetsw_->updateDatasetList();
 pc_->updateChannelList();
 paneCompensation_->updateForm();
 dogating();
 isUpdating_ = wasUpdating;
 dothelayout();
}

void MainWindow::resizeEvent(QResizeEvent* e)
{
 QMainWindow::resizeEvent(e);
 dothelayout();
}
  
 // // Event: User drags something onto widget
void MainWindow::dragEnterEvent(QDragEnterEvent* event) 
{
 if(event->mimeData()->hasFormat("text/uri-list"))
   event->acceptProposedAction();
}


 // // Event: User drops MIME onto widget
void MainWindow::dropEvent(QDropEvent* event)
{
 try
 {
  for(QUrl url : event->mimeData()->urls())
  {
   QFile qf(url.toLocalFile()); //  * f = new File(url.path());
   QFileInfo qfi(qf);
   lastDirectory_ = qfi.absoluteDir();
   loadFile(qf);
  }
 }
 catch (Facs_IOException e)
 {
  // TO DO ...
  // e->printStackTrace();
 }
}

//#ifdef HIDE_THREAD

void _MainWindow_GateCalcThread::callbackDoneCalc(Dataset* dataset)
{
 emit callbackDoneCalc_signal(dataset);
}
 

//GateCalcThread MainWindow::calcthread = new GateCalcThread;
//{
//};

//#endif // def HIDE_THREAD
 
// // Action: New project
void MainWindow::actionNewProject()
{
 project_ = new FacsanaduProject();
 updateall();
}
 
// // Open a project
void MainWindow::actionOpenProject()
{
 QFileDialog dia; // = new QFileDialog();
 dia.setFileMode(QFileDialog::ExistingFile);
 dia.setDirectory(lastDirectory_.absolutePath());
 dia.setNameFilter(tr("Project files") + " (*.facsanadu)");
 if(dia.exec())
 {
  QFile qf( dia.selectedFiles().value(0) );
  QFileInfo qfi(qf);
  lastDirectory_ = qfi.absoluteDir();
  try
  {
   // //  do we want to use XML? ...
   // project_ = FacsanaduXML::importXML(f);
   currentProjectFile_ = qfi.absoluteFilePath();
  }
  catch (Facs_IOException e)
  {
   //QTutil.showNotice(this, e.getMessage());
   //e.printStackTrace();
  }
  updateall();
 } 
}
  
// // Action: Save project
void MainWindow::actionSaveProject()
{
 if( currentProjectFile_.isEmpty() )
   actionSaveProjectAs();

 else 
 {
  try
  {
   // // xml?
    // FacsanaduXML.exportToFile(project, currentProjectFile);
  }
  catch (Facs_IOException e)
  {
   // QTutil.showNotice(this, e.getMessage());
   // e.printStackTrace();
  }
 }
}
 
// // Action: Save as... file
void MainWindow::actionSaveProjectAs()
{
 QFileDialog dia; // = new QFileDialog();
 dia.setFileMode(QFileDialog::AnyFile);
 dia.setAcceptMode(QFileDialog::AcceptSave);
 dia.setDirectory(lastDirectory_.absolutePath());
 dia.setDefaultSuffix("facsanadu");
 dia.setNameFilter(tr("Project files")+" (*.facsanadu)");

 if( dia.exec() )
 {
  QFile qf(dia.selectedFiles().value(0));
  QFileInfo qfi(qf);
  lastDirectory_ = qfi.absoluteDir();
  currentProjectFile_ = qfi.absoluteFilePath();
  actionSaveProject();
 }
}
  
// // Action: Export graphs
void MainWindow::actionExportGraphs()
{
 LinkedList<Dataset*> listds = getSelectedDatasets();
 LinkedList<ViewSettings*> listviews = getSelectedViews();
 
 GraphExportWindow w; // = new GraphExportWindow();
 w.exec();
 if( w.wasOk() )
 {
  QFileDialog dia; //= new QFileDialog();
  dia.setFileMode(QFileDialog::AnyFile);
  dia.setNameFilter( tr("Image files)") + " (*.png)" );
  dia.setAcceptMode(QFileDialog::AcceptSave);
  dia.setDefaultSuffix("png");

  if( dia.exec() )
  {
   try
   {
    QFile qf(dia.selectedFiles().value(0));
    GraphExporter::render(qf, project_, listds, listviews, w.splitByDataset(), w.splitByView(), w.getWidth(), w.getHeight());
   }
   catch (Facs_RuntimeException e)
   {
    // QTutil.showNotice(this, e.getMessage());
    // e.printStackTrace();
   }
  } 
 }
}
 
// //
void MainWindow::actionExportStatistics()
{
 paneStats_->actionExportCSV();
}
 
void MainWindow::actionExportCSV()
{
 try
 {
  LinkedList<Dataset*> dsList = datasetsw_->getSelectedDatasets();

  if(dsList.isEmpty())
  {
   // QTutil.printError(this, tr("No datasets selected"));
  }
  else if(dsList.size()==1)
  {
   QFileDialog dia; // =new QFileDialog();
   dia.setFileMode(QFileDialog::AnyFile);
   dia.setNameFilter(tr("CSV files (*.csv)"));
   dia.setAcceptMode(QFileDialog::AcceptSave);
   dia.setDefaultSuffix("csv"); 
 
   if( dia.exec() )
   {
    try
    {
     QFile qf(dia.selectedFiles().value(0));
     ExportFcsToCSV::save(dsList.value(0), 
      qf);
     /*
      PrintWriter fw=new PrintWriter();
      fw.println(tableStats.allToCSV());
      fw.close();
     */
    }
    catch (Facs_IOException e)
    {
//     QTutil.showNotice(this, e.getMessage());
//     e.printStackTrace();
    }
   } 
  }
  else
  {
   QFileDialog dia; // =new QFileDialog();
   dia.setFileMode(QFileDialog::DirectoryOnly);
   //dia.setNameFilter(tr("CSV files (*.csv)"));
   dia.setAcceptMode(QFileDialog::AcceptSave);
   //dia.setDefaultSuffix("csv"); 

   if( dia.exec() )
   {
    try
    {
     for(Dataset* oneDataset : dsList)
     {
      QFile parent(dia.selectedFiles().value(0));
       // //  why do we need parent?
      QFile qf(oneDataset->getName() + ".csv", &parent);
      ExportFcsToCSV::save(oneDataset, qf); ////parent, 
        //qf));
     }
    }
    catch (Facs_IOException e)
    {
//     QTutil.showNotice(this, e.getMessage());
//     e.printStackTrace();
    }
   } 
  }
 }
 catch (Facs_Exception e)
 {
//  QTutil.printError(this, tr("Failed to save file: ")+e.getMessage());
//  e.printStackTrace();
 }
}
 
// // Load one file
void MainWindow::loadFile(QFile& path) // throws IOException
{
 project_->addDataset(path);
 handleEvent(EventDatasetsChanged());
}

 
// // Get selected views
LinkedList<ViewSettings*> MainWindow::getSelectedViews()
{
 return viewsw_->getSelectedViews();
}


// // Get selected datasets
LinkedList<Dataset*> MainWindow::getSelectedDatasets()
{
 return datasetsw_->getSelectedDatasets();
}


void MainWindow::actionDsChanged()
{
 //Update list of selected datasets, in a thread neutral list

 // synchronized (mutex) //selDatasetsCache_)
 {
  QMutexLocker lock(&selDatasetsCache_mutex_);
  selDatasetsCache_.clear();
  selDatasetsCache_.append(datasetsw_->getSelectedDatasets());
 }

 //Better to send a signal here instead?
 paneViews_->invalidateCache();
 dogating();
 dothelayout();
 paneMetadata_->updateForm();
}

// // Get selected gates
LinkedList<Gate*> MainWindow::getSelectedGates()
{
 return gatesw_->getSelectedGates();
}

// // Update gating results
void MainWindow::dogating()
{
 //For speed, only do selected ones
 //project.performGating(getSelectedDatasets());
 calcthread_->wakeup();
}
 
 /**
  * Entry point
  */
// public static void main(String[] args)
// {
// QApplication.initialize(QtProgramInfo.programName, args);
// QCoreApplication.setApplicationName(QtProgramInfo.programName);
// new MainWindow();
// QTutil.execStaticQApplication(); 
// }

// // Event bus
void MainWindow::handleEvent(FacsanaduEvent* event)
{
 switch(event->get_description())
 // if(event instanceof EventGatesChanged)
 {
 case FacsanaduEvent::Description::EventGatesChanged:
  gatesw_->updateGatesList();
  paneViews_->invalidateCache();
  dogating();
  dothelayout();
  break;

  //else if(event instanceof EventViewsChanged) 
 case FacsanaduEvent::Description::EventViewsChanged:
  viewsw_->updateViewsList(); //just added. problem?
  paneViews_->invalidateCache();
  dogating();
  dothelayout();
  break;

 //else if(event instanceof EventCompensationChanged)
 case FacsanaduEvent::Description::EventCompensationChanged:
  project_->updateCompensation();
  dogating();
  dothelayout();
  break;
 
  //else if(event instanceof EventGatesMoved)
 case FacsanaduEvent::Description::EventGatesMoved:
  dothelayout();
  break;

  //else if(event instanceof EventDatasetsChanged)
 case FacsanaduEvent::Description::EventDatasetsChanged:
  datasetsw_->updateDatasetList();
  paneViews_->invalidateCache();
  dogating();
  paneMetadata_->updateForm();
  break;
  //else if(event instanceof EventSetViewTool)
  //{
  //?paneViews.setTool(((EventSetViewTool) event).choice);
  //}
 default:
  throw new Facs_RuntimeException; // ...  ("!!!");
  break;
 }
}

void MainWindow::dothelayout()
{
 if(!isUpdating_)
 {
  paneViews_->updateViews();
  paneStats_->updateStats();
  paneProfile_->updateViews();
  QApplication::processEvents();
  //or flush?
 }
}

// // Add a gate with a suggested parent
void MainWindow::addGate(Gate* suggestParent, Gate* g)
{
 gatesw_->addGate(suggestParent, g);
}

// // Get currently selected measures
LinkedList<GateMeasure*> MainWindow::getSelectedMeasures()
{
 return gatesw_->getSelectedMeasures();
}
 
// // Show About-information
void MainWindow::actionAbout()
{
 (new DialogAbout())->exec();
}

 
// // Open up website
void MainWindow::actionWebsite()
{
 QDesktopServices::openUrl(QUrl("http://www.facsanadu.org"));
}

 
// // Set number of CPU cores
void MainWindow::actionSetNumCores()
{
 int th = QInputDialog::getInt(this, QtProgramInfo::programName, 
   tr("Number of cores: "), calcthread_->getNumCores());

 if( (th >= 1) && (th <= 128) )
   calcthread_->setNumCores(th);
}


void MainWindow::recalcProfChan(ProfChannel* chChanged)
{
 // TODO Auto-generated method stub
 project_->recalcProfChan(chChanged);
 dothelayout();
 //handleEvent(new EventViewsChanged()); //maybe too light
}

// // Ensure proper exit
// @Override
void MainWindow::closeEvent(QCloseEvent* arg)
{
 QMainWindow::closeEvent(arg);
 exit(0);
}

#ifdef HIDE

#endif //def HIDE

