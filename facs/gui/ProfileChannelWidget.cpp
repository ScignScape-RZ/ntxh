// // license___here

#include "ProfileChannelWidget.h"

#include "resource/ImgResource.h"

#include "lengthprofile/ProfilePane.h"

#include "qt/QTutil.h"

#include "MainWindow.h"

#include "FacsanaduProject.h"

#include "../data/ProfChannel.h"


#include <QHeaderView>

#define connect_this(x, y, z) connect(y, &x, \
   this, &ProfileChannelWidget::z);


ProfileChannelWidget::ProfileChannelWidget(MainWindow* mw)
  :  mw_(mw)
{
 //? setMargin(0);

 main_layout_ = new QVBoxLayout;

 isUpdating_ = false;
 tableDatasets_ = new QTableWidget;
 paneProfile_ = new ProfilePane(mw_); //
 
 tableDatasets_->setColumnCount(1);
 tableDatasets_->verticalHeader()->hide();
 tableDatasets_->setHorizontalHeaderLabels({tr("Prof.Channel")}); 
    //Arrays.asList(tr("Prof.Channel")));
 tableDatasets_->setSelectionBehavior(
   QAbstractItemView::SelectionBehavior::SelectRows);
 tableDatasets_->horizontalHeader()->setSectionResizeMode(
   QHeaderView::ResizeMode::ResizeToContents);
 tableDatasets_->horizontalHeader()->setStretchLastSection(true); 

// tableDatasets_->selectionModel().selectionChanged.connect(this,"dothelayout()");
 connect_this(QItemSelectionModel ::selectionChanged 
   ,tableDatasets_->selectionModel() ,dothelayout) 

 QPushButton* bAddChannel = new QPushButton(tr("Create prof.channel"), this);
 QPushButton* bRemoveDataset = new QPushButton( 
   QIcon(ImgResource::icon_delete), "", this);
 
 connect_this(QPushButton ::clicked ,bAddChannel ,actionAddChannel) 
 connect_this(QPushButton ::clicked ,bRemoveDataset ,actionRemoveChannel) 
 connect_this(QItemSelectionModel ::selectionChanged 
   ,tableDatasets_->selectionModel() ,actionSelectionChanged) 


// bAddChannel.clicked.connect(this,"actionAddChannel()");
// bRemoveDataset.clicked.connect(this,"actionRemoveChannel()");
// tableDatasets_->selectionModel().selectionChanged.connect(this,"actionSelectionChanged()");
 
 main_layout_->addWidget(tableDatasets_);
 main_layout_->addLayout(QTutil::layoutHorizontal({bAddChannel, bRemoveDataset}));

 tableDatasets_->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
}

void ProfileChannelWidget::dothelayout()
{
 mw_->dothelayout();
}
 
 
void ProfileChannelWidget::updateChannelList()
{
 FacsanaduProject* project = mw_->project();
 bool wasUpdating = isUpdating_;
 isUpdating_ = false;
 tableDatasets_->setRowCount( project->profchan().size() );

 int row = 0;

 for(ProfChannel* chan : project->profchan() )
 {
  QTableWidgetItem* qtwi = QTutil::createReadOnlyItem(chan->getName());   //Maybe separate columns here
  qtwi->setData(Qt::ItemDataRole::UserRole, QVariant::fromValue( (void*)chan ) );
  tableDatasets_->setItem(row, 0, qtwi);
  ++row;
 }
 isUpdating_ = wasUpdating;
}

void ProfileChannelWidget::actionSelectAllDataset()
{
 tableDatasets_->selectAll();
}

 
// // Action: Create channel
void ProfileChannelWidget::actionAddChannel()
{
 FacsanaduProject* project = mw_->project();

 for( int chid : paneProfile_->getSelChans() )
 {
  ProfChannel* ch = new ProfChannel();
  ch->set_channel(chid);
  project->profchan().append(ch);
  
  updateChannelList();
  tableDatasets_->selectionModel()->select(
    tableDatasets_->model()->index(tableDatasets_->rowCount() - 1, 0),
    QItemSelectionModel::SelectionFlag::ClearAndSelect);
 
  mw_->recalcProfChan(nullptr);
  break; //Only create one?
 }
}

 
// // Action: Remove selected channels
void ProfileChannelWidget::actionRemoveChannel()
{
 FacsanaduProject* project = mw_->project();

 for(ProfChannel* pc : getSelectedChannels())
   project->profchan().removeAll(pc);

 //project->profchan()->removeAll(getSelectedChannels());
 updateChannelList();
 mw_->recalcProfChan(nullptr);
}


LinkedList<ProfChannel*> ProfileChannelWidget::getSelectedChannels()
{
 LinkedList<ProfChannel*> selviews; // = new LinkedList<ProfChannel*>();

 for( QModelIndex in : tableDatasets_->selectionModel()->selectedRows() )
   selviews.append( (ProfChannel*) tableDatasets_->item(in.row(),0)->data(
     Qt::ItemDataRole::UserRole).value<void*>());

 return selviews;
}

void ProfileChannelWidget::actionSelectionChanged()
{
 // ProfChannel* ch = nullptr;
  // //  this is weird ...
 //for(ProfChannel* c : getSelectedChannels())
 //  ch = c;
 //  I assume the point is just to get the last item in the list ...

 ProfChannel* ch = getSelectedChannels().last();

 paneProfile_->setCurChan(ch);
}

