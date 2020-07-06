
// // license___here_h


#ifndef DatasetInfoPane__H
#define DatasetInfoPane__H

#include <QWidget>
#include <QTableWidget>
#include <QTableWidgetItem>

// package facsanadu.gui.panes;


// // Pane showing metadata about a dataset
class DatasetInfoPane : public QWidget
{
 QTableWidget* tableMatrix_; // =new QTableWidget();
 MainWindow* mw_;
 bool updating; // =false;
  
 public: 
  DatasetInfoPane(MainWindow* mw);
 
 void updateForm();

 void dataChanged(QTableWidgetItem* it);

};

#endif // __H
 



