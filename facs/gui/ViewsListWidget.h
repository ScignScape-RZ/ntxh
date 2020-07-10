
// // license___here_h

#ifndef ViewsListWidget__H
#define ViewsListWidget__H


#include <QDialog>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QCheckBox>
#include <QPushButton>

#include <QWidget>

// // temp
#include<QList>
#define LinkedList QList


class MainWindow;
class ViewSettings;


class ViewsListWidget : public QWidget //: QVBoxLayout
{
 QVBoxLayout* main_layout_;

 bool isUpdating_; //=false;

 QTableWidget* tableViews_; // =new QTableWidget(); 

 MainWindow* mw_;
 
public:
 
 ViewsListWidget(MainWindow* mw);
 
 void dothelayout();
 
 void actionSelectAllViews();

 // // Get selected views
 LinkedList<ViewSettings*> getSelectedViews(); 
 
 // // Update list with views
 void updateViewsList();

 // // Action: Remove selected views
 void actionRemoveView();

 // // Action: Create a new view
 void actionNewView();
};

#endif // __H
 



