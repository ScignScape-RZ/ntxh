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

#include "GraphExportWindow.h"

#include "view/GraphExporter.h"

#include "../data/ExportFcsToCSV.h"
#include "../data/Dataset.h"

#include "events/FacsanaduEvent.h"

#include <QMenu>
#include <QMimeData>
#include <QFile>
#include <QFileDialog>


//#ifdef HIDE

struct Facs_IOException {};
struct Facs_RuntimeException {};
struct Facs_Exception {};


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

#ifdef HIDE_THREAD

GateCalcThread MainWindow::calcthread=new GateCalcThread()
{
 FacsanaduProject getProject()
 {
  return project;
 }
 void callbackDoneCalc(Dataset dataset)
 {
  QApplication.invokeLater(new Runnable()
  {
   public void run()
   {
    updateall();
           //System.out.println("Thread called");
   }
  });
 }
 Collection<Dataset> getCurrentDatasets()
 {
  synchronized (selDatasetsCache)
  {
   ArrayList<Dataset> d=new ArrayList<Dataset>(selDatasetsCache);
   return d;
  }
 }
};

#endif // def HIDE_THREAD
 
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
 handleEvent(new EventDatasetsChanged());
}

#ifdef HIDE

 
// // Get selected views
LinkedList<ViewSettings> MainWindow::getSelectedViews()
{
 return viewsw.getSelectedViews();
}

// // Get selected datasets
LinkedList<Dataset> MainWindow::getSelectedDatasets()
{
 return datasetsw.getSelectedDatasets();
}

void MainWindow::actionDsChanged()
{
 //Update list of selected datasets, in a thread neutral list
 synchronized (selDatasetsCache)
 {
  selDatasetsCache.clear();
  selDatasetsCache.addAll(datasetsw.getSelectedDatasets());
 }
 //Better to send a signal here instead?
 paneViews.invalidateCache();
 dogating();
 dothelayout();
 paneMetadata.updateForm();
}
 
// // Get selected gates
LinkedList<Gate> MainWindow::getSelectedGates()
{
 return gatesw.getSelectedGates();
}


// // Update gating results
void MainWindow::dogating()
{
 //For speed, only do selected ones
 //project.performGating(getSelectedDatasets());
 calcthread.wakeup();
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
 if(event instanceof EventGatesChanged)
 {
  gatesw.updateGatesList();
  paneViews.invalidateCache();
  dogating();
  dothelayout();
 }
 else if(event instanceof EventViewsChanged)
 {
  viewsw.updateViewsList(); //just added. problem?
  paneViews.invalidateCache();
  dogating();
  dothelayout();
 }
 else if(event instanceof EventCompensationChanged)
 {
  project.updateCompensation();
  dogating();
  dothelayout();
 }
 else if(event instanceof EventGatesMoved)
 {
  dothelayout();
 }
 else if(event instanceof EventDatasetsChanged)
 {
  datasetsw.updateDatasetList();
  paneViews.invalidateCache();
  dogating();
  paneMetadata.updateForm();
 }
 else if(event instanceof EventSetViewTool)
 {
  paneViews.setTool(((EventSetViewTool) event).choice);
 }
 else
   throw new RuntimeException("!!!");
}

void MainWindow::dothelayout()
{
 if(!isUpdating)
 {
  paneViews.updateViews();
  paneStats.updateStats();
  paneProfile.updateViews();
  QApplication.processEvents();
  //or flush?
 }
}

// // Add a gate with a suggested parent
void MainWindow::addGate(Gate suggestParent, Gate g)
{
 gatesw.addGate(suggestParent, g);
}

// // Get currently selected measures
LinkedList<GateMeasure> MainWindow::getSelectedMeasures()
{
 return gatesw.getSelectedMeasures();
}
 
// // Show About-information
void MainWindow::actionAbout()
{
 new DialogAbout().exec();
}
 
// // Open up website
void MainWindow::actionWebsite()
{
 QDesktopServices.openUrl(new QUrl("http://www.facsanadu.org"));
}
 
// // Set number of CPU cores
void MainWindow::actionSetNumCores()
{
 int th=QInputDialog.getInt(this, QtProgramInfo.programName, tr("Number of cores: "), calcthread.getNumCores());
 if(th>=1 && th<=128)
   calcthread.setNumCores(th);
}

void MainWindow::recalcProfChan(ProfChannel chChanged)
{
 // TODO Auto-generated method stub
 project.recalcProfChan(chChanged);
 dothelayout();
 //handleEvent(new EventViewsChanged()); //maybe too light
}

// // Ensure proper exit
// @Override
void MainWindow::closeEvent(QCloseEvent arg)
{
 super.closeEvent(arg);
 System.exit(0);
}

#endif //def HIDE

