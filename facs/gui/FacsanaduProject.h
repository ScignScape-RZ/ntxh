
// // license___here_h

#ifndef FacsanaduProject__H
#define FacsanaduProject__H

#include <QDialog>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QCheckBox>
#include <QPushButton>

// // temp
#include<QList>
#define LinkedList QList


#include<QMap>


class GateSet;
class Dataset;
class ViewSettings; // =new LinkedList<ViewSettings>();
class ProfChannel; 
class GatingResult;
class Compensation;

class ChannelInfo;

//package facsanadu.gui;

// //

class FacsanaduProject
{
 GateSet* gateset_; // =new GateSet();
 LinkedList<Dataset*> datasets_; // =new LinkedList<Dataset>();
 LinkedList<ViewSettings*> views_; // =new LinkedList<ViewSettings>();
 LinkedList<ProfChannel*> profchan_; // =new LinkedList<ProfChannel>();

 //HashMap<Dataset*, GatingResult*> ...
 QMap<Dataset*, GatingResult*> gatingResult_; // =new HashMap<Dataset, GatingResult>();

 Compensation* compensation_; // =new Compensation();
 
 // // Get gating result for dataset
 GatingResult* getGatingResult(Dataset* ds);
// {
//  return getCreateGatingResult(ds); //Why a separate method here??
// }

 // // Get an existing or create a new gating result for a particular dataset. Each dataset should have one
 GatingResult* getCreateGatingResult(Dataset* ds);
 
 // // Update gating results
 void performGating(LinkedList<Dataset> listDatasets);

 void addDataset(QFile path); // throws IOException;

 void updateCompensation();
 void addDataset(Dataset* ds);
 int getNumChannels();

 //ArrayList<ChannelInfo> getChannelInfo();
 QList<ChannelInfo*> getChannelInfo();
 
 void recalcProfChan();

};

#endif // __H
 


