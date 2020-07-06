
// // license___here_h

#ifndef MainWindow__H
#define MainWindow__H

/**
 * 
 * The main window
 * 
 * @author Johan Henriksson
 *
 */
class MainWindow : public QMainWindow
{
 //private 
 Collection<Dataset> selDatasetsCache=new LinkedList<Dataset>();

 QTabWidget tabwidget_; //=new QTabWidget();
 QMenuBar menubar_; //=new QMenuBar();
 GatesListWidget gatesw_; //=new GatesListWidget(this);
 ProfileChannelWidget pc_; //=new ProfileChannelWidget(this);
 ViewsListWidget viewsw_; //=new ViewsListWidget(this);
 DatasetListWidget datasetsw_; //=new DatasetListWidget(this);
 CompensationPane paneCompensation_; //=new CompensationPane(this);
 DatasetInfoPane paneMetadata_; //=new DatasetInfoPane(this);
 
 ViewsPane paneViews_;
 GateStatsPane paneStats_;
 ProfilePane paneProfile_;
 
 File currentProjectFile_ ; //=null;
 
 boolean isUpdating_; //=false;

 File lastDirectory_; //=new File("."); 

 FacsanaduProject* project_; // = new FacsanaduProject();

 
 // // Update all widgets
 void updateall();


protected:
 
 // // Event: Widget resized
 void resizeEvent(QResizeEvent e);
 
 // // Event: User drags something onto widget
 void dragEnterEvent(com.trolltech.qt.gui.QDragEnterEvent event);

 // // Event: User drops MIME onto widget
 void dropEvent(QDropEvent event);

 FacsanaduProject* project_;

public:
 
 //FacsanaduProject* project();
  // = new FacsanaduProject();

 GateCalcThread calcthread; //=new GateCalcThread(){

 FacsanaduProject* getProject();

 // // Constructor
 MainWindow();

 
 // // Action: New project
 void actionNewProject();
 
 // // Open a project
 void actionOpenProject();
 
 // // Action: Save project
 void actionSaveProject();
 
 // // Action: Save as... file
 void actionSaveProjectAs();
 
 // // Action: Export graphs
 void actionExportGraphs();
 
 // // Export everything to CSV
 void actionExportStatistics();
 
 void actionExportCSV();
 
 // // Load one file
 void loadFile(File path) throws IOException;

 // // Get selected views
 LinkedList<ViewSettings> getSelectedViews();
 
 // // Get selected datasets
 LinkedList<Dataset> getSelectedDatasets();

 void actionDsChanged();
 
 // // Get selected gates
 LinkedList<Gate> getSelectedGates();

 // // Update gating results
 void dogating();
 
/*
 static void main(String[] args)
 {
 QApplication.initialize(QtProgramInfo.programName, args);
 QCoreApplication.setApplicationName(QtProgramInfo.programName);
 new MainWindow();
 QTutil.execStaticQApplication(); 
 }
*/

 // // Event bus
 void handleEvent(FacsanaduEvent event);
 
 void dothelayout();

 // // Add a gate with a suggested parent
 void addGate(Gate suggestParent, Gate g);

 // // Get currently selected measures
 public LinkedList<GateMeasure> getSelectedMeasures();

 // // Show About-information
 public void actionAbout();
 
 // // Open up website
 public void actionWebsite();
 
 // // Set number of CPU cores
 public void actionSetNumCores();

 public void recalcProfChan(ProfChannel chChanged);

 // // Ensure proper exit
// @Override
// protected void closeEvent(QCloseEvent arg)
// {
// super.closeEvent(arg);
// System.exit(0);
// }
 
};

#endif // __H
 

