
// // license___here_h


#ifndef AddMeasureDialog__H
#define AddMeasureDialog__H

// // temp
#include<QList>
#define LinkedList QList


#include <QTableWidget>
#include <QCheckBox>
#include <QPushButton>
#include <QDialog>

// package facsanadu.gui;

class FacsanaduProject;
class ChannelInfo;
class GateMeasure;



// //

class AddMeasureDialog : public QDialog
{
 QTableWidget* tableChannels_; //=new QTableWidget();
 QCheckBox* cbMean_; // =new QCheckBox(tr("Mean"));
 QCheckBox* cbMedian_; //=new QCheckBox(tr("Median"));
 QCheckBox* cbSD_; //=new QCheckBox(tr("Standard deviation"));
 QPushButton* bOk_; //=new QPushButton(tr("OK"));
 QPushButton* bCancel_; //=new QPushButton(tr("Cancel"));
 
 FacsanaduProject* project_;

 bool wasOK_;
 
public: 

 AddMeasureDialog(FacsanaduProject* proj);

 FacsanaduProject* project() 
 {
  return project_;
 }


 void actionOK();
 void updatechanlist();
 
 // // Get selected channels
 LinkedList<ChannelInfo*> getSelectedChannels();
 
 //Collection<GateMeasure*> getMeasures();
 QList<GateMeasure*> getMeasures();

};

#endif // __H
 
