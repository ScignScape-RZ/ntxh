
// // license___here_h

#ifndef MainWindow__H
#define MainWindow__H

#include "GateCalcThread.h"


#include "events/FacsanaduEvent.h"

#include <QDialog>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QCheckBox>
#include <QPushButton>

#include <QMainWindow>
#include <QResizeEvent>
#include <QDropEvent>
#include <QMetaObject>
#include <QDragEnterEvent>

#include <QFile>
#include <QDir>

#include <QTabWidget>
#include <QMenuBar>
#include <QMutex>


// // temp
#include<QList>
#define LinkedList QList


class GatesListWidget; //* gatesw_; //=new GatesListWidget(this);
class ProfileChannelWidget; //* pc_; //=new ProfileChannelWidget(this);
class ViewsListWidget; //* viewsw_; //=new ViewsListWidget(this);
class DatasetListWidget; //* datasetsw_; //=new DatasetListWidget(this);
class CompensationPane; //* paneCompensation_; //=new CompensationPane(this);
class DatasetInfoPane; //* paneMetadata_; //=new DatasetInfoPane(this);
 
class ViewsPane; //* paneViews_;
class GateStatsPane; //* paneStats_;
class ProfilePane; //* paneProfile_;
class FacsanaduProject; //* project_; // = new FacsanaduProject();
class GateCalcThread;

class ViewSettings;
class Dataset;
class Gate;
class FacsanaduEvent;
class GateMeasure;
class ProfChannel;


// // The main window

//#ifdef HIDE


class _MainWindow_GateCalcThread;

class MainWindow : public QMainWindow
{
 //private 
  //? Collection<Dataset> selDatasetsCache=new LinkedList<Dataset>();

 QList<Dataset*> selDatasetsCache_;
 QMutex selDatasetsCache_mutex_;

 QTabWidget* tabwidget_; //=new QTabWidget();
 QMenuBar* menubar_; //=new QMenuBar();
 GatesListWidget* gatesw_; //=new GatesListWidget(this);
 ProfileChannelWidget* pc_; //=new ProfileChannelWidget(this);
 ViewsListWidget* viewsw_; //=new ViewsListWidget(this);
 DatasetListWidget* datasetsw_; //=new DatasetListWidget(this);
 CompensationPane* paneCompensation_; //=new CompensationPane(this);
 DatasetInfoPane* paneMetadata_; //=new DatasetInfoPane(this);
 
 ViewsPane* paneViews_;
 GateStatsPane* paneStats_;
 ProfilePane* paneProfile_;
 
 QString currentProjectFile_ ; //=null;
 
 bool isUpdating_; //=false;

 QDir lastDirectory_; //=new File("."); 

 FacsanaduProject* project_; // = new FacsanaduProject();

 GateCalcThread* calcthread_; 
 
 // // Update all widgets
 void updateall();


protected:
 
 // // Event: Widget resized
 void resizeEvent(QResizeEvent* e);
 
 // // Event: User drags something onto widget
 void dragEnterEvent(QDragEnterEvent* event);

 // // Event: User drops MIME onto widget
 void dropEvent(QDropEvent* event);

 // // Ensure proper exit
 void closeEvent(QCloseEvent* arg) Q_DECL_OVERRIDE;

// FacsanaduProject* project_;

public:
 
 //FacsanaduProject* project();
  // = new FacsanaduProject();

 FacsanaduProject* getProject();
 FacsanaduProject* project() 
 {
  return getProject();
 }


 // // Constructor
 MainWindow();

 QDir lastDirectory()
 {
  return lastDirectory_;
 }
 
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
 void loadFile(QFile& path); // throws IOException;

 // // Get selected views
 LinkedList<ViewSettings*> getSelectedViews();
 
 // // Get selected datasets
 LinkedList<Dataset*> getSelectedDatasets();

 void actionDsChanged();
 
 // // Get selected gates
 LinkedList<Gate*> getSelectedGates();

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
 void handleEvent(FacsanaduEvent* event);

  // temp ...
 void handleEvent(FacsanaduEvent event)
 {
  handleEvent(&event); 
 }
 
 void dothelayout();

 // // Add a gate with a suggested parent
 void addGate(Gate* suggestParent, Gate* g);

 // // Get currently selected measures
 LinkedList<GateMeasure*> getSelectedMeasures();

 // // Show About-information
 void actionAbout();
 
 // // Open up website
 void actionWebsite();
 
 // // Set number of CPU cores
 void actionSetNumCores();

 void recalcProfChan(ProfChannel* chChanged);

 // // Ensure proper exit
// @Override
// protected void closeEvent(QCloseEvent arg)
// {
// super.closeEvent(arg);
// System.exit(0);
// }
 
};

// //  need equivalent of an anonymous inner class in Java ...

class _MainWindow_GateCalcThread : public QObject, public GateCalcThread 
{
 Q_OBJECT

 FacsanaduProject* project;

public:

 _MainWindow_GateCalcThread(FacsanaduProject* p) 
   : project(p) {} 

 FacsanaduProject* getProject() Q_DECL_OVERRIDE
 {
  return project;
 }

 void callbackDoneCalc(Dataset* dataset);
 QList<Dataset*> getCurrentDatasets();

Q_SIGNALS:

 void callbackDoneCalc_signal(Dataset*);

};



//#endif //def HIDE

#endif // __H
 

