
// // license___here

#include "GraphExportWindow.h"


GraphExportWindow::GraphExportWindow()
{
 spWidth_ = new QSpinBox();
 spHeight_ = new QSpinBox();
 
 bOk_ = new QPushButton(tr("OK"));
 bCancel_ = new QPushButton(tr("Cancel"));

 bAsOne_ = new QRadioButton(tr("All in one"));
 bByDataset_ = new QRadioButton(tr("Split by dataset"));
 bByView_ = new QRadioButton(tr("Split by view"));
 bAllSeparate_ = new QRadioButton(tr("All graphs individually"));

 bool wasOk_ = false;

 spWidth.setMinimum(100);
 spWidth.setMaximum(10000);
 spWidth.setValue(500);

 spHeight.setMinimum(100);
 spHeight.setMaximum(10000);
 spHeight.setValue(400);
  
 QButtonGroup bg = new QButtonGroup();
 bg.addButton(bAsOne);
 bg.addButton(bByDataset);
 bg.addButton(bByView);
 bg.addButton(bAllSeparate);

 bAsOne.setChecked(true);
  
 QLayout lay = QTutil.layoutVertical
 (
  QTutil.withLabel(tr("Width:"), spWidth),
  QTutil.withLabel(tr("Height:"), spHeight),
  bAsOne,
  bByDataset,
  bByView,
  bAllSeparate,
  QTutil.layoutHorizontal(bOk,bCancel)
 );

 setLayout(lay);
  
 //bOk.clicked.connect(this,"actionOK()");
 //bCancel.clicked.connect(this,"actionCancel()");
}
 
 
bool GraphExportWindow::splitByDataset()
{
 return bByView.isChecked() || bAllSeparate.isChecked();
}

bool GraphExportWindow::splitByView()
{
 return bByDataset.isChecked() || bAllSeparate.isChecked();
}
 
int GraphExportWindow::getWidth()
{
 return spWidth.value();
}

int GraphExportWindow::getHeight()
{
 return spHeight.value();
}
 
void GraphExportWindow::actionOK()
{
 if(storeAnnot())
 {
  wasOk=true;
  close();
 }
}

bool GraphExportWindow::storeAnnot()
{
 return true;
}
 
void GraphExportWindow::actionCancel()
{
 close();
}

