
// // license___here_h


#ifndef ViewsMatrix__H
#define ViewsMatrix__H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>


// package facsanadu.gui.panes;

// //
class ViewsMatrix : public QWidget
{
 QGridLayout* layViews_;// = new QGridLayout();
 MainWindow* mw_;

 LinkedList<QLabel>* headerHorizontal_; //=new LinkedList<QLabel>();
 LinkedList<QVLabel>* headerVertical_; //=new LinkedList<QVLabel>();
 ArrayList<ArrayList<ViewWidget>>* prevChanWidget_; // = new ArrayList<ArrayList<ViewWidget>>();
 bool orderDataset_; // = false;
 int maxevents_;

public: 

 ViewToolChoice currentTool_; // =ViewToolChoice.SELECT;
 
 ViewsMatrix(MainWindow* mw); 
 
 // // Update the layout of everything
 void updateViews();
 void setMaxEvents(int maxevents);
 void setTool(ViewToolChoice choice);
 void invalidateCache();
};

#endif // __H
 



