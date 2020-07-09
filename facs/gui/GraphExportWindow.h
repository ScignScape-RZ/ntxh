
// // license___here_h

#ifndef GraphExportWindow__H
#define GraphExportWindow__H

#include <QDialog>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QCheckBox>
#include <QPushButton>
#include <QSpinBox>
#include <QRadioButton>


class GraphExportWindow : public QDialog
{
 QSpinBox* spWidth_; //= new QSpinBox();
 QSpinBox* spHeight_; //= new QSpinBox();
 
 QPushButton* bOk_; //= new QPushButton(tr("OK"));
 QPushButton* bCancel_; //= new QPushButton(tr("Cancel"));

 QRadioButton* bAsOne_; // =new QRadioButton(tr("All in one"));
 QRadioButton* bByDataset_; // =new QRadioButton(tr("Split by dataset"));
 QRadioButton* bByView_; // =new QRadioButton(tr("Split by view"));
 QRadioButton* bAllSeparate_; // =new QRadioButton(tr("All graphs individually"));
 
 bool wasOk_;

public:

 bool wasOk() { return wasOk_; } // =false;

 GraphExportWindow();
 
 bool splitByDataset();
 bool splitByView();
 int getWidth();
 int getHeight();
 void actionOK();

 bool storeAnnot();
 void actionCancel(); 
};

#endif // __H
 


