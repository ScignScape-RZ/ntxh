

// // license___here_h


#ifndef DatasetListWidget__H
#define DatasetListWidget__H



// package facsanadu.gui;

#include <QVBoxLayout>
#include <QTableWidget>
#include <QCheckBox>
#include <QPushButton>

#include "events/FacsanaduEvent.h"

// // temp
#include<QList>
#define LinkedList QList


class MainWindow;
class Dataset;

// // List of all datasets

class DatasetListWidget : public QWidget
{
 Q_OBJECT

 QVBoxLayout* main_layout_;
 MainWindow* mw_;
 
 bool isUpdating_ = false;

 QTableWidget* tableDatasets_; // =new QTableWidget();

 void emitEvent(FacsanaduEvent event);

public: 
  
 //?
 //QSignalEmitter::Signal0 selectionChanged_; // =new QSignalEmitter.Signal0();
 
 DatasetListWidget(MainWindow* mw);

 void dothelayout();

 // // Update list with datasets
 void updateDatasetList();

 void actionSelectAllDatasets();
 
 void actionAddDatasets();
 
 void actionRemoveDataset();

 void actionMoveUp();
 
 void actionMoveDown();

 // // Get selected datasets
 LinkedList<Dataset*> getSelectedDatasets();

Q_SIGNALS: 
 void selectionChanged();


};

#endif // __H
 

