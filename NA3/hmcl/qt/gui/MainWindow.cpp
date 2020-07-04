
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
 
 paneViews_;
 paneStats_;
 paneProfile_;
 
 currentProjectFile_ = nullptr;

 lastDirectory_ = new File(".");
 
 isUpdating_ = false;

 setMenuBar(menubar);

 ImgResource.setWindowIcon(this);
 
 paneViews=new ViewsPane(this);
 paneStats=new GateStatsPane(this);
 paneProfile=new ProfilePane(this);
 pc.paneProfile=paneProfile;
 
 QMenu mFile=menubar.addMenu(tr("File"));
 mFile.addAction(tr("New project"), this, "actionNewProject()");
 mFile.addAction(tr("Open project"), this, "actionOpenProject()");
 mFile.addAction(tr("Save project"), this, "actionSaveProject()");
 mFile.addAction(tr("Save project as"), this, "actionSaveProjectAs()");
 mFile.addSeparator();
 mFile.addAction(tr("Exit"), this, "close()");

 
 QMenu mExport=menubar.addMenu(tr("Export"));
 mExport.addAction(tr("Graphs"), this, "actionExportGraphs()");
 mExport.addAction(tr("Statistics"), this, "actionExportStatistics()");
 mExport.addAction(tr("Dataset as CSV"), this, "actionExportCSV()");

 QMenu mSettings=menubar.addMenu(tr("Settings"));
 mSettings.addAction(tr("Set number of CPU cores"), this, "actionSetNumCores()");
 menubar.addSeparator();
 
 QMenu mHelp=menubar.addMenu(tr("Help"));
 mHelp.addAction(tr("About"), this, "actionAbout()");
 mHelp.addAction(tr("Website"), this, "actionWebsite()");

 datasetsw.selectionChanged.connect(this,"actionDsChanged()");
 
 QVBoxLayout layLeft=new QVBoxLayout();
 layLeft.addLayout(datasetsw);
 layLeft.addLayout(viewsw);
 layLeft.addLayout(gatesw);
 layLeft.addLayout(pc);

 viewsw.actionNewView();

 
 /// Load all files from directory
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
 

 
 tabwidget.addTab(paneViews, tr("Graphs"));
 tabwidget.addTab(paneStats, tr("Statistics"));
 tabwidget.addTab(paneProfile, tr("Length profiles"));
 tabwidget.addTab(paneCompensation, tr("Compensation"));
 tabwidget.addTab(paneMetadata, tr("Dataset info"));

 QHBoxLayout lay=new QHBoxLayout();
 lay.addLayout(layLeft);
 lay.addWidget(tabwidget);
 
 QWidget cent=new QWidget();
 cent.setLayout(lay);
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
 pc.updateChannelList();
 paneCompensation.updateForm();
 dogating();
 isUpdating=wasUpdating;
 dothelayout();
}
 

void MainWindow::resizeEvent(QResizeEvent e)
{
 super.resizeEvent(e);
 dothelayout();
}
 
 
 // // Event: User drags something onto widget
void MainWindow::dragEnterEvent(com.trolltech.qt.gui.QDragEnterEvent event) 
{
 if(event.mimeData().hasFormat("text/uri-list"))
   event.acceptProposedAction();
}

 // // Event: User drops MIME onto widget
void MainWindow::dropEvent(QDropEvent event)
{
 try
 {
  for(QUrl url : event.mimeData().urls())
  {
   File* f = new File(url.path());
   lastDirectory = f.getParentFile();
   loadFile(f);
  }
 }
 catch (IOException e)
 {
  e.printStackTrace();
 }
}

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

 
// // Action: New project
void MainWindow::actionNewProject()
{
 project = new FacsanaduProject();
 updateall();
}
 
// // Open a project
void MainWindow::actionOpenProject()
{
 QFileDialog dia = new QFileDialog();
 dia.setFileMode(FileMode.ExistingFile);
 dia.setDirectory(lastDirectory.getAbsolutePath());
 dia.setNameFilter(tr("Project files") + " (*.facsanadu)");
 if(dia.exec()!=0)
 {
  File f = new File(dia.selectedFiles().get(0));
  lastDirectory=f.getParentFile();
  try
  {
   project=FacsanaduXML.importXML(f);
   currentProjectFile=f;
  }
  catch (IOException e)
  {
   QTutil.showNotice(this, e.getMessage());
   e.printStackTrace();
  }
  updateall();
 } 
}
 
 
// // Action: Save project
void MainWindow::actionSaveProject()
{
 if(currentProjectFile==nullptr)
   actionSaveProjectAs();

 if(currentProjectFile!=nullptr)
 {
  try
  {
   FacsanaduXML.exportToFile(project, currentProjectFile);
  }
  catch (IOException e)
  {
   QTutil.showNotice(this, e.getMessage());
   e.printStackTrace();
  }
 }
}
 
// // Action: Save as... file
void MainWindow::actionSaveProjectAs()
{
 QFileDialog* dia = new QFileDialog();
 dia->setFileMode(FileMode.AnyFile);
 dia->setAcceptMode(AcceptMode.AcceptSave);
 dia->setDirectory(lastDirectory.getAbsolutePath());
 dia->setDefaultSuffix("facsanadu");
 dia->setNameFilter(tr("Project files")+" (*.facsanadu)");
 if(dia.exec()!=0)
 {
  File f = new File(dia.selectedFiles().get(0));
  lastDirectory=f->getParentFile();
  currentProjectFile = f;
  actionSaveProject();
 }
}

  
// // Action: Export graphs
void MainWindow::actionExportGraphs()
{
 LinkedList<Dataset> listds=getSelectedDatasets();
 LinkedList<ViewSettings> listviews=getSelectedViews();
 
 GraphExportWindow w = new GraphExportWindow();
 w.exec();
 if(w.wasOk)
 {
  QFileDialog dia=new QFileDialog();
  dia.setFileMode(FileMode.AnyFile);
  dia.setNameFilter(tr("Image files)")+" (*.png)");
  dia.setAcceptMode(AcceptMode.AcceptSave);
  dia.setDefaultSuffix("png");

  if(dia.exec()!=0)
  {
   try
   {
    File f=new File(dia.selectedFiles().get(0));
    GraphExporter.render(f, project, listds, listviews, w.splitByDataset(), w.splitByView(), w.getWidth(), w.getHeight());
   }
   catch (RuntimeException e)
   {
    QTutil.showNotice(this, e.getMessage());
    e.printStackTrace();
   }
  } 
 }
}
 
// //
void MainWindow::actionExportStatistics()
{
 paneStats.actionExportCSV();
}
 
void MainWindow::actionExportCSV()
{
 try
 {
  LinkedList<Dataset> dsList=datasetsw.getSelectedDatasets();

  if(dsList.isEmpty())
  {
   QTutil.printError(this, tr("No datasets selected"));
  }
  else if(dsList.size()==1)
  {
   QFileDialog dia=new QFileDialog();
   dia.setFileMode(FileMode.AnyFile);
   dia.setNameFilter(tr("CSV files (*.csv)"));
   dia.setAcceptMode(AcceptMode.AcceptSave);
   dia.setDefaultSuffix("csv"); 
 
   if(dia.exec()!=0)
   {
    try
    {
     ExportFcsToCSV.save(dsList.get(0), new File(dia.selectedFiles().get(0)));
     /*
      PrintWriter fw=new PrintWriter();
      fw.println(tableStats.allToCSV());
      fw.close();
     */
    }
    catch (IOException e)
    {
     QTutil.showNotice(this, e.getMessage());
     e.printStackTrace();
    }
   } 
  }
  else
  {
   QFileDialog dia=new QFileDialog();
   dia.setFileMode(FileMode.DirectoryOnly);
   //dia.setNameFilter(tr("CSV files (*.csv)"));
   dia.setAcceptMode(AcceptMode.AcceptSave);
   //dia.setDefaultSuffix("csv"); 

   if(dia.exec()!=0)
   {
    try
    {
     for(Dataset oneDataset:dsList)
     {
      File parent=new File(dia.selectedFiles().get(0));
      ExportFcsToCSV.save(oneDataset, new File(parent, oneDataset.getName()+".csv"));
     }
    }
    catch (IOException e)
    {
     QTutil.showNotice(this, e.getMessage());
     e.printStackTrace();
    }
   } 
  }
 }
 catch (Exception e)
 {
  QTutil.printError(this, tr("Failed to save file: ")+e.getMessage());
  e.printStackTrace();
 }
}
 
// // Load one file
void MainWindow::loadFile(File path) throws IOException
{
 project.addDataset(path);
 handleEvent(new EventDatasetsChanged());
}

 
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
void MainWindow::handleEvent(FacsanaduEvent event)
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
 

