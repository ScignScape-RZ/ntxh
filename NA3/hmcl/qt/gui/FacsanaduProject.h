//package facsanadu.gui;

// //

class FacsanaduProject
{
 GateSet* gateset_; // =new GateSet();
 LinkedList<Dataset> datasets_; // =new LinkedList<Dataset>();
 LinkedList<ViewSettings> views_; // =new LinkedList<ViewSettings>();
 LinkedList<ProfChannel> profchan_; // =new LinkedList<ProfChannel>();

 HashMap<Dataset, GatingResult> gatingResult_; // =new HashMap<Dataset, GatingResult>();

 Compensation compensation_; // =new Compensation();
 
 // // Get gating result for dataset
 GatingResult getGatingResult(Dataset ds);
 {
  return getCreateGatingResult(ds); //Why a separate method here??
 }

 // // Get an existing or create a new gating result for a particular dataset. Each dataset should have one
 GatingResult* getCreateGatingResult(Dataset ds);
 
 // // Update gating results
 void performGating(LinkedList<Dataset> listDatasets);

 void addDataset(File path) throws IOException;

 void updateCompensation();
 void addDataset(Dataset ds);
 int getNumChannels();

 ArrayList<ChannelInfo> getChannelInfo();

 void recalcProfChan();

};

