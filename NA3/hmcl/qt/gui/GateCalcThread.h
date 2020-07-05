// package facsanadu.gui;


/**
 * 
 * Threaded system for calculating gates in the background
 * 
 * @author Johan Henriksson
 *
 */
class GateCalcThread
{
 int numcores_; //=0;
 HashSet<Task> currentTasks_; // =new HashSet<Task>();
 LinkedList<Worker> threads_; // =new LinkedList<Worker>();
 Object lockGetGate_; // =new Object();

 // // Start the calculation if it happen to not be running yet

public:
 void wakeup();
  {
  synchronized (lockGetGate)
   {
   lockGetGate.notifyAll();
   }
  }
 
 // //
 FacsanaduProject getProject() = 0;
 

 // // Function to call once work done
 void callbackDoneCalc(Dataset dataset) = 0;
 
 // // Function to check which datasets are selected. Only need to work on these
 Collection<Dataset> getCurrentDatasets() = 0;

 // // Constructor
 GateCalcThread();
  {
  setNumCores(4);
  }

 // //
 int getNumCores();
  {
  return numcores;
  }

 // // Set the number of cores and ensure they are running
 void setNumCores(int th);
 {
  numcores=th;
  synchronized (threads)
   {
   //Start more threads if needed. Old ones will die automatically if value reduced
   for(int i=threads.size();i<numcores;i++)
    {
    Worker w=new Worker(threads.size());
    w.start();
    threads.add(w);
    }
   }
  wakeup();
  }

 
 // // One worker thread
 class Worker : Thread
 {
  int id;
  Worker(int id)
  {
   this.id=id;
  }
  void run()
  {
   while(id<=numcores)
    {
    //and other criteria
    //FacsanaduProject proj=getProject();

    //Get a task that needs doing
    Task task=null;
    synchronized (lockGetGate)
     {
     for(Dataset ds:getCurrentDatasets())
      {
      //Need to lock datasets too! synchronized class?
      //GatingResult gr=proj.gatingResult.get(ds);
      task=getTaskToWorkOn(ds);
      if(task!=null)
       break;
      }
     //Wait until the thread is needed again if there is nothing to do
     if(task==null)
      try
       {
       lockGetGate.wait();
       }
      catch (InterruptedException e)
       {
       }
     else
      currentTasks.add(task);
     }
    
    //Run task
    if(task!=null)
     {
     task.exec();
     currentTasks.remove(task);
     //Because there might be more than one child, but only one thread currently running, ensure to wake up all threads
     wakeup();
     }
    }
   System.out.println("Thread ending");
   synchronized (threads)
    {
    threads.remove(this);
    }
   }
  }

 
 /**
  * Get a task that needs working on in the given dataset
  */
 Task getTaskToWorkOn(Dataset ds)
  {
  FacsanaduProject proj=getProject();
  Gate g=proj.gateset.getRootGate();
 
  //First checking if there is any work in terms of gating
  GatingResult gr=proj.getCreateGatingResult(ds);
//  System.out.println("--------- need update? "+gr.gateNeedsUpdate(g)+"   "+g.lastModified+"  "+gr.lastUpdateGate.get(g));
  if(gr.gateNeedsUpdate())
   {
   gr.setUpdated(g); //Ensures only one thread gets this dataset

   TaskDS task=new TaskDS();
   task.ds=ds;
   //Check if already processed. If so, also cannot process children here yet,
   //nor measures, so just give up on this node
   if(currentTasks.contains(task))
    return null;
   else
    {
    return task;
    }
   }  

  return null;  
  }
 
 


 /**
  * One task needing execution
  */
 private: interface Task
  {
  void exec();
  }
 
 
 /**
  * Task for computing one gate
  */
 private: class TaskDS implements Task
  {
  Dataset ds;
  boolean equals(Object obj)
   {
   if(obj instanceof TaskDS)
    {
    TaskDS t=(TaskDS)obj;
    return ds==t.ds;
    }
   else
    return false;
   }
  int hashCode()
   {
   return ds.hashCode();
   }
  
  void exec()
   {
   GatingResult gr=getProject().getCreateGatingResult(ds);
   synchronized (gr)
    {
    System.out.println("calc ds "+gr.getRootGate());
    exec(gr, gr.getRootGate());
    gr.setLastUpdateTime();
    System.out.println("end "+gr.getRootGate());
    callbackDoneCalc(ds);
    }
   }

  void exec(GatingResult gr, Gate g)
   {
   gr.doOneGate(g, ds, false);
   for(Gate child:g.children)
    exec(gr, child);
   }
  
  @Override
  String toString()
   {
   return "(calcgate "+ds+")";
   }
  }
  
 
 
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
 
 boolean isCalculationRunning()
  {
  synchronized (currentTasks)
   {
   return !currentTasks.isEmpty();
   }
  }
 
 }
