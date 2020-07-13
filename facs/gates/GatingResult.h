

// // license___here_h


#ifndef GatingResult__H
#define GatingResult__H


// package facsanadu.gates;

class Gate;
class Dataset;
class GateSet;
class GateMeasure;


/**
 * 
 * 
 * @author Johan Henriksson
 *
 */
class GatingResult
{
 QMap<Gate*, QList<int> > acceptedFromGate_; //=new HashMap<Gate, QList<int>>();
 QMap<GateMeasure*, double> gatecalc_;//=new HashMap<GateMeasure, Double>();
 QList<int> globalGateRes_; //=new QList<int>();

 /**
  * Do gating for a gate with a parent
  */
 void dogateRec(Gate* g, Dataset* ds);
 
 void classifyobs(Gate* g, Dataset* ds, QList<int> passedGateRes, int id); 
 long lastGatingCalculationTime_; // =0;
 GateSet* gating_; //=new GateSet();

 
public:

 long lastUpdateGate_; //=0;
 void setUpdated(Gate* g);

 GatingResult(GateSet* gating);
 int getGateIntIDForObs(int obs);
 
 // // Perform gating for all gates
 void perform(GateSet* gating, Dataset* ds);

 // //Calculate for one gate
 void doOneGate(Gate* g, Dataset* ds, bool approximate);
 
 /**
  * Set accepted result from a gate
  */
 void setAcceptedFromGate(Gate* g, QList<int> res, long lastMod);
 
 QList<Gate*> getIdGates();

 int getTotalCount();

 Gate* getRootGate();

 double getCalcResult(GateMeasure* calc);

 /**
  * Check if this gate needs any updating.
  * Done by having a time last computed vs a time for when last modified
  */
 bool gateNeedsUpdate();

 QList<int> getAcceptedFromGate(Gate* g);

 long lastGatingCalculationTime();

 void setLastUpdateTime();

};


#endif // GatingResult__H


