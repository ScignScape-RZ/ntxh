
// // license___here

#include "GraphExportWindow.h"

#include "qt/QTutil.h"

#include <QButtonGroup>


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

 wasOk_ = false;

 spWidth_->setMinimum(100);
 spWidth_->setMaximum(10000);
 spWidth_->setValue(500);

 spHeight_->setMinimum(100);
 spHeight_->setMaximum(10000);
 spHeight_->setValue(400);
  
 QButtonGroup* bg = new QButtonGroup();
 bg->addButton(bAsOne_);
 bg->addButton(bByDataset_);
 bg->addButton(bByView_);
 bg->addButton(bAllSeparate_);

 bAsOne_->setChecked(true);
  
 QLayout* lay = QTutil::layoutVertical
 ({
  QTutil::withLabel(tr("Width:"), spWidth_),
  QTutil::withLabel(tr("Height:"), spHeight_),
  bAsOne_,
  bByDataset_,
  bByView_,
  bAllSeparate_,
  QTutil::layoutHorizontal({bOk_, bCancel_})
  });

 setLayout(lay);
  
 //bOk.clicked.connect(this,"actionOK()");
 //bCancel.clicked.connect(this,"actionCancel()");
}
 
 
bool GraphExportWindow::splitByDataset()
{
 return bByView_->isChecked() || bAllSeparate_->isChecked();
}

bool GraphExportWindow::splitByView()
{
 return bByDataset_->isChecked() || bAllSeparate_->isChecked();
}
 
int GraphExportWindow::getWidth()
{
 return spWidth_->value();
}

int GraphExportWindow::getHeight()
{
 return spHeight_->value();
}
 
void GraphExportWindow::actionOK()
{
 if(storeAnnot())
 {
  wasOk_ = true;
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

