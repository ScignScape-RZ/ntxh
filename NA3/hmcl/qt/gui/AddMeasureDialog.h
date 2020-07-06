
// // license___here_h


#ifndef AddMeasureDialog__H
#define AddMeasureDialog__H



// package facsanadu.gui;


// //

class AddMeasureDialog : public QDialog
{
 QTableWidget* tableChannels_; //=new QTableWidget();
 QCheckBox* cbMean_; // =new QCheckBox(tr("Mean"));
 QCheckBox* cbMedian_; //=new QCheckBox(tr("Median"));
 QCheckBox* cbSD_; //=new QCheckBox(tr("Standard deviation"));
 QPushButton* bOk_; //=new QPushButton(tr("OK"));
 QPushButton* bCancel_; //=new QPushButton(tr("Cancel"));
 
 FacsanaduProject* proj;
 
 public: 

 AddMeasureDialog(FacsanaduProject proj);

 void actionOK();
 void updatechanlist();
 
 // // Get selected channels
 LinkedList<ChannelInfo> getSelectedChannels();
 
 Collection<GateMeasure> getMeasures();

};

#endif // __H
 
