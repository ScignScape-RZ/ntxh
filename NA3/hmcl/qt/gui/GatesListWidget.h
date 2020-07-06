

// // license___here_h

#ifndef GatesListWidget__H
#define GatesListWidget__H

//package facsanadu.gui;

#include <QDialog>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QCheckBox>
#include <QPushButton>

class MainWindow;
class CallbackColor;
class Gate;
class GateMeasure;

/**
 * 
 * List of all gates
 * 
 * @author Johan Henriksson
 *
 */
class GatesListWidget //?: public.QVBoxLayout
{
 QVBoxLayout* main_layout_;


 boolean isUpdating;

 QTreeWidget* treeGates_; //=new QTreeWidget();
 MainWindow* mw_; //
 LinkedList<CallbackColor*> callbacks_; //=new LinkedList<GatesListWidget.CallbackColor>();

 void updateGatesListRecursive(QTreeWidgetItem parentItem, final Gate g, LinkedList<Gate> selgates, LinkedList<GateMeasure> selcalc);

 void addMeasures(QTreeWidgetItem parentItem, Gate g, LinkedList<GateMeasure> selcalc);

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
 



