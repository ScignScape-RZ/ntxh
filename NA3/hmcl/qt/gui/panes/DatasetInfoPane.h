// package facsanadu.gui.panes;


// // Pane showing metadata about a dataset
class DatasetInfoPane : QWidget
{
 QTableWidget* tableMatrix_; // =new QTableWidget();
 MainWindow* mw_;
 bool updating; // =false;
  
 public: 
  DatasetInfoPane(MainWindow mw);
 
 void updateForm();

 void dataChanged(QTableWidgetItem it);

};


