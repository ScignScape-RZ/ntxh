

// // license___here_h

#ifndef GatesListWidget__H
#define GatesListWidget__H

//package facsanadu.gui;

#include <QDialog>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QCheckBox>
#include <QPushButton>

#include <QTreeWidget>
#include <QTreeWidgetItem>

#include <QWidget>

// // temp
#include<QList>
#define LinkedList QList


class MainWindow;
class CallbackColor;
class Gate;
class GateMeasure;
class FacsanaduEvent;

// // List of all gates
class GatesListWidget : public QWidget //?: public.QVBoxLayout
{
Q_OBJECT

 QVBoxLayout* main_layout_;


 bool isUpdating_;

 QTreeWidget* treeGates_; //=new QTreeWidget();
 MainWindow* mw_; //
 LinkedList<CallbackColor*> callbacks_; //=new LinkedList<GatesListWidget.CallbackColor>();

 void updateGatesListRecursive(QTreeWidgetItem* parentItem, // final 
   const Gate* g, LinkedList<Gate*> selgates, 
   LinkedList<GateMeasure*> selcalc);

 void addMeasures(QTreeWidgetItem* parentItem, Gate* g, LinkedList<GateMeasure*> selcalc);

 void emitEvent(FacsanaduEvent event);
//  {
//  mw.handleEvent(event);
//  }

 //private interface CallbackColor
 // {
 // void set();
 // }

public: 

 GatesListWidget(MainWindow* mw);
 
 void dothelayout(); 
 void actionSelectAllGates();

 // // Get the currently selected gate or null 
 Gate* getCurrentGate();

 // //  Get selected gates
 LinkedList<Gate*> getSelectedGates();

 // // Get selected measures
 LinkedList<GateMeasure*> getSelectedMeasures();
 
 // // Update list with gates
 void updateGatesList();
 
 // //
 void actionAddMeasure();
 
 // //Rename current gate
 void actionRenameGate();

 
 // // Action: Remove selected gates
 void actionRemoveGates();
 
 // // Add a new gate
 void addGate(Gate* suggestParent, Gate* g);
};

#endif // __H
 



