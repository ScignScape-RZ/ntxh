

// // license___here_h


#ifndef GATE_INFO__H
#define GATE_INFO__H

#include <QString>

#include <QColor>

class GateMeasure; 

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

 QList<GateMeasure*> getMeasures() const
 {
  return {};
 }

 QList<Gate*> children() const
 {
  return {};
 }

 QString name() const
 {
  return name_;
 }

 void set_name(QString name)
 {
  name_ = name;
 }

 void setUpdated();
 void detachParent();
                   
 QColor color() const
 {
  return QColor();
 }

 void attachMeasure(GateMeasure* calc);

};


class GateColor
{
 QColor qc_;

public:

 GateColor(QColor qc) : qc_(qc) {}


};



#endif // GATE_INFO__H


