
// // license___here

#include "AddMeasureDialog.h"

#include "qt/QTutil.h"

#include "FacsanaduProject.h"
#include "../data/ChannelInfo.h"

#include "../gates/measure/GateMeasure.h"
#include "../gates/measure/GateMeasureUnivariate.h"
#include "../gates/measure/GateMeasureMean.h"




#include <QHeaderView>

// package facsanadu.gui;


// //

#define connect_this(x, y, z) connect(y, &x, \
   this, &AddMeasureDialog::z);

AddMeasureDialog::AddMeasureDialog(FacsanaduProject* proj)
  :  wasOK_(true)
{
 tableChannels_ = new QTableWidget();
 cbMean_ = new QCheckBox(tr("Mean"));
 cbMedian_ = new QCheckBox(tr("Median"));
 cbSD_ = new QCheckBox(tr("Standard deviation"));
 bOk_ = new QPushButton(tr("OK"));
 bCancel_ = new QPushButton(tr("Cancel"));
 
 project_ = proj;
 
 tableChannels_->setColumnCount(1);
 tableChannels_->verticalHeader()->hide();
 tableChannels_->setHorizontalHeaderLabels({tr("Channel")});
 tableChannels_->setSelectionBehavior(
   QAbstractItemView::SelectionBehavior::SelectRows);
 tableChannels_->horizontalHeader()->setSectionResizeMode(
   QHeaderView::ResizeMode::ResizeToContents);
 tableChannels_->horizontalHeader()->setStretchLastSection(true); 

 connect_this(QPushButton ::clicked ,bOk_ ,actionOK) 
 connect_this(QPushButton ::clicked ,bCancel_ ,close) 

// bOk.clicked.connect(this,"actionOK()");
// bCancel.clicked.connect(this,"close()");
 
 updatechanlist();

 setLayout(QTutil::layoutVertical({tableChannels_, cbMean_, cbMedian_, cbSD_,
   QTutil::layoutHorizontal({bOk_, bCancel_})}));
 
 setMinimumSize(200, 400);
}

//? boolean wasOK=false;

void AddMeasureDialog::actionOK()
{
 wasOK_ = true;
 close();
}
 
void AddMeasureDialog::updatechanlist()
{
 int row=0;

 QList<ChannelInfo*> chans = project_->getChannelInfo();

 tableChannels_->setRowCount(chans.size());

 for(int i = 0; i < chans.size(); i++)
 {
  ChannelInfo* ci = chans.at(i);
  QTableWidgetItem* it = QTutil::createReadOnlyItem(ci->formatName());
  it->setData(Qt::ItemDataRole::UserRole, QVariant::fromValue( (void*) ci ) );
  tableChannels_->setItem(row, 0, it);
  row++;
 }
}
 
 // // Get selected channels
LinkedList<ChannelInfo*> AddMeasureDialog::getSelectedChannels()
{
 LinkedList<ChannelInfo*> selviews; // =new LinkedList<ChannelInfo>();

 for(QModelIndex in : tableChannels_->selectionModel()->selectedRows())
 {
  selviews.append((ChannelInfo*) tableChannels_->item(in.row(), 0)
    ->data(Qt::ItemDataRole::UserRole).value<void*>() );
 }
 return selviews;
}
 
QList<GateMeasure*> AddMeasureDialog::getMeasures()
{
 LinkedList<GateMeasure*> list; // =new LinkedList<GateMeasure>();
 if(wasOK_)
 {
  QList<ChannelInfo*> chans = project_->getChannelInfo();

  for(ChannelInfo* info : getSelectedChannels())
  {
   int i = chans.indexOf(info);
   if(cbMean_->isChecked())
   {
    GateMeasureMean* c = new GateMeasureMean();
    c->channelIndex = i;
    list.append(c);
   }
  }
 }
 return list;
}

