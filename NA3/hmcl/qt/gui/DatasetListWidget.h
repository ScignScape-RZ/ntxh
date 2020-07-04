// package facsanadu.gui;


// // List of all datasets

class DatasetListWidget
{
 QVBoxLayout* main_layout_;
 MainWindow* mw_;
 
 bool isUpdating_ = false;

 QTableWidget* tableDatasets_; // =new QTableWidget();

 void emitEvent(FacsanaduEvent event);

public: 
  
 //?
 QSignalEmitter.Signal0 selectionChanged_; // =new QSignalEmitter.Signal0();
 
 DatasetListWidget(MainWindow* mw);
 void dothelayout();

 // // Update list with datasets
 void updateDatasetList();

 void actionSelectAllDataset();
 
 void actionAddDatasets();
 
 void actionRemoveDataset();

 void actionMoveUp();
 
 void actionMoveDown();

 // // Get selected datasets
 LinkedList<Dataset> getSelectedDatasets();

};


