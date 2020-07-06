
// // license___here_h


#ifndef GateStatsPane__H
#define GateStatsPane__H


// package facsanadu.gui.panes;


// // Johan Henriksson
class GateStatsPane : QWidget
{
 QTableWidgetWithCSVcopy* tableStats_; // =new QTableWidgetWithCSVcopy();
  
 MainWindow* mw_;
  
 QCheckBox* cbShowParent_; //=new QCheckBox(tr("Show % of parent"));
 QCheckBox* cbShowTotal_; //=new QCheckBox(tr("Show % of total"));
 QPushButton* bCopyCSV_; //=new QPushButton(tr("Export to clipboard"));
  
 GateStatsPane(MainWindow* mw);
  
 void updateStats();

 static QString formatPerc(double d);
  
 // // Copy all of table to clipboard
 void actionCopyToClipboard();
 
 // // Export everything to CSV
 void actionExportCSV();

};

#endif // __H
 

