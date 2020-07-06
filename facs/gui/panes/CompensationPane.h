
// // license___here_h


#ifndef CompensationPane__H
#define CompensationPane__H

#include <QWidget>

// package facsanadu.gui.panes;

class QTableWidgetWithCSVcopy;

// // Pane showing compensation

class CompensationPane : public QWidget
{
 QTableWidgetWithCSVcopy* tableMatrix_; // =new QTableWidgetWithCSVcopy();
 MainWindow* mw_;
 bool updating_; // =false;
  
public: 

 CompensationPane(MainWindow* mw);
 void updateForm();
 void dataChanged(QTableWidgetItem* it);
};

#endif // __H
 



