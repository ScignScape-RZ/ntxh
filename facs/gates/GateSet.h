

// // license___here_h


#ifndef GateSet__H
#define GateSet__H

#include <QString>
#include <QSet>


// // temp
#include<QList>
#define LinkedList QList

//package facsanadu.gates;

class Gate;

// // A set of gates
class GateSet
{
 Gate* rootgate_; // =new GateRoot();

 void getGatesRecursively(Gate* parent, LinkedList<Gate*> list);

 static Gate* getGate(QString name, Gate* parent);

 void getIdGates(Gate* g, QList<Gate*> list);

public:
 
 GateSet(); //{ rootgate.name="root"; }
 
 Gate* getRootGate()
 {
  return rootgate_;
 }

 void addNewGate(Gate* g); // {rootgate.attachChild(g);}

 QList<Gate*> getGates();

 QSet<QString> getGateNames();

 // // Get a free name for a gate
 QString getFreeName();

 Gate getGate(QString name);

 QList<Gate*> getIdGates();

};

#endif //ndef GateSet__H



