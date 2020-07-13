

// // license___here_h


#ifndef GATE_INFO__H
#define GATE_INFO__H

#include <QString>

#include <QColor>
#include <QObject>


class GateMeasure; 

// //  just a minimal wrapper to bridge Facsanadu and cytoLib ...
class Gate : public QObject
{
Q_OBJECT

 QString name_;
 void* oc_gate_;

public:

 Gate(QString name)
  : name_(name), oc_gate_(nullptr)
 {
 }

 Gate(const Gate&);
 Gate();

 QList<GateMeasure*> getMeasures() const
 {
  return {};
 }

 QList<Gate*> children() const;

 void attachChild(Gate* g); 

 QString name() const
 {
  return name_;
 }

 virtual QString class_name() const
 {
  return {};
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

Q_DECLARE_METATYPE(Gate)
Q_DECLARE_METATYPE(Gate*)
Q_DECLARE_METATYPE(const Gate*)


class GateColor
{
 QColor qc_;

public:

 GateColor(QColor qc) : qc_(qc) {}

 int r() { return qc_.red(); }
 int g() { return qc_.green(); }
 int b() { return qc_.blue(); }
 

};




#endif // GATE_INFO__H


