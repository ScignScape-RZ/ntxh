
// // license___here_h

#ifndef GateCalcThread__H
#define GateCalcThread__H


// package facsanadu.gui;

#include <QThread>
#include <QSet>
#include <QMutex>

// // temp
#include<QList>
#define LinkedList QList

class FacsanaduProject;
class Dataset;
class GatingResult;
class Gate;

// // Threaded system for calculating gates in the background

class GateCalcThread //: public QObject
{

// Q_O

public:
 class Worker; // =new LinkedList<Worker>();
 class Task;

private:

 int numcores_; //=0;
 //HashSet<Task> currentTasks_; // =new HashSet<Task>();

 QSet<Task*> currentTasks_;
 LinkedList<Worker> threads_; // =new LinkedList<Worker>();

 //? Object lockGetGate_; // =new Object();
 QMutex lockGetGate_;

 // // Start the calculation if it happen to not be running yet

public:

 void wakeup();
 
 // //
 virtual FacsanaduProject* getProject() = 0;
 

 // // Function to call once work done
 virtual void callbackDoneCalc(Dataset* dataset) = 0;
 
 // // Function to check which datasets are selected. Only need to work on these
  //Collection<Dataset> getCurrentDatasets() = 0;
 virtual QList<Dataset*> getCurrentDatasets() = 0;

 // // Constructor
 GateCalcThread();

 // //
 int getNumCores();

 // // Set the number of cores and ensure they are running
 void setNumCores(int th);
 
 // // One worker thread
 class Worker : QThread
 {
  int id;
  Worker(int id);
  void run();
 };

 /**
  * Get a task that needs working on in the given dataset
  */
 Task* getTaskToWorkOn(Dataset* ds);

 // // One task needing execution
//private: 

 class Task
  {
   virtual void exec() = 0;
  };
 
 
 // // Task for computing one gate
 private: 
  class TaskDS : Task
  {
   Dataset* ds;
   bool equals(void* obj); // Object?
  };

public:

 int hashCode();
 void exec();

 void exec(GatingResult gr, Gate g);
  
 QString toString(); // Q_DECL_OVERRIDE;
  
 
 
 /**
  * 
  * previews: best to have a separate flag in the gatingresult.
  * 
  * then in all functions above, a flag to request preview results. if all previews done, proceed with the full thing
  * 
  * in addition, there should be some functions to get high priority datasets... and views?
  * 
  * ORDER:
  * preview prio datasets
  * full prio datasets
  * full all datasets      <--- note: no need to compute previews unless they are actually being displayed!!
  * 
  * 
  * TODO: also have a callback whenever some data has been computed
  * 
  * also a function to check if all work has been done or not.
  * it is done if there are no current tasks and one cannot get any more tasks. or just checking if any tasks are running
  * 
  */
 
 bool isCalculationRunning();
 
};

#endif // __H
 

