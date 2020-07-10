

// // license___here_h


#ifndef GATE_INFO__H
#define GATE_INFO__H

#include <QString>

// //  just a minimal wrapper to bridge Facsanadu and cytoLib ...
class Gate
{
 QString name_;
 void* oc_gate_;

public:

 Gate(QString name)
  : name_(name), oc_gate_(nullptr)
 {
 }

 QString name()
 {
  return name_;
 }


};

#endif // GATE_INFO__H


