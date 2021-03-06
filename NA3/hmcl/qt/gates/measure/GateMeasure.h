
// // license___here_h


#ifndef GateMeasure__H
#define GateMeasure__H

// package facsanadu.gates.measure;

#include <QString>

class Gate;
class Dataset;
class GatingResult;
class FacsanaduProject;

// // Calculation for a gate
class GateMeasure
{
 Gate* gate_;

public:

 GateMeasure();

 Gate* gate()
 {
  return gate_;
 }
 
 double calc(Dataset* ds, Gate* g, GatingResult* res);
 QString getDesc(FacsanaduProject* proj);
 
 
 void detachFromGate();
};

#endif // GateMeasure__H


