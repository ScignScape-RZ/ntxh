
// // license___here_h


#ifndef QTableWidgetWithCSVcopy__H
#define QTableWidgetWithCSVcopy__H

#include <QString>


// package facsanadu.gui.qt;


// //Much of code inspired from stack overflow

class QTableWidgetWithCSVcopy : //extends QTableWidget
{
protected: 

 void keyPressEvent(com.trolltech.qt.gui.QKeyEvent event);

public:

 QString allToCSV();
 void copy(TreeSet<Integer> whichcol, TreeSet<Integer> whichrow);
 
 /**
  * Export selection to CSV
  */
 QString toCSV(TreeSet<Integer> whichcol, TreeSet<Integer> whichrow);

 /**
  * Export everything to CSV. Can return null if no
  */
 QString selectionToCSV();
 
 void copyAll();

 void copy();
};

#endif // __H
 



