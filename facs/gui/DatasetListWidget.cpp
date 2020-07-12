
// // license___here

#include "DatasetListWidget.h"


#include "qt/QTutil.h"

#include "MainWindow.h"
#include "FacsanaduProject.h"

#include "view/ViewSettings.h"

#include "events/FacsanaduEvent.h"

#include "resource/ImgResource.h"

#include "../data/Dataset.h"

#include <QHeaderView>
#include <QFileDialog>


#define connect_this(x, y, z) connect(y, &x, \
   this, &DatasetListWidget::z);

// package facsanadu.gui;

DatasetListWidget::DatasetListWidget(MainWindow* mw) 
 :  mw_(mw)
{ 
 main_layout_ = new QVBoxLayout;
 isUpdating_ = false;

 tableDatasets_ = new QTableWidget();

  // selectionChanged = new QSignalEmitter.Signal0();
 
  //? setMargin(0);
  
 tableDatasets_->setColumnCount(1);
 tableDatasets_->verticalHeader()->hide();
 tableDatasets_->setHorizontalHeaderLabels({tr("Dataset")});
 tableDatasets_->setSelectionBehavior(
   QAbstractItemView::SelectionBehavior::SelectRows);
 tableDatasets_->horizontalHeader()->setSectionResizeMode(
   QHeaderView::ResizeMode::ResizeToContents);
 tableDatasets_->horizontalHeader()->setStretchLastSection(true);  

// tableDatasets_->selectionModel().selectionChanged.connect(this,"dothelayout()");
 connect_this(QItemSelectionModel ::selectionChanged 
   ,tableDatasets_->selectionModel() ,dothelayout) 

 QPushButton* bAddDataset = new QPushButton(tr("Add dataset"), this);
 QPushButton* bSelectAllDataset = new QPushButton(tr("Select all"), this);
 QPushButton* bRemoveDataset = new QPushButton(
   QIcon(ImgResource::icon_delete), "", this);
  
 QPushButton* bMoveUp = new QPushButton(QIcon(ImgResource::moveUp), "", this);
 QPushButton* bMoveDown = new QPushButton(QIcon(ImgResource::moveDown), "", this);
  
 connect_this(QPushButton ::clicked ,bAddDataset ,actionAddDatasets) 
 connect_this(QPushButton ::clicked ,bRemoveDataset ,actionRemoveDataset) 
 connect_this(QPushButton ::clicked ,bSelectAllDataset ,actionSelectAllDatasets) 
 connect_this(QPushButton ::clicked ,bMoveUp ,actionMoveUp) 
 connect_this(QPushButton ::clicked ,bMoveDown ,actionMoveDown) 

 main_layout_->addWidget(tableDatasets_);

 main_layout_->addLayout(QTutil::layoutHorizontal({
   bMoveUp, bMoveDown, bAddDataset, bSelectAllDataset, bRemoveDataset}));

 tableDatasets_->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
}

void DatasetListWidget::dothelayout()
{
 emit selectionChanged();
}
  
void DatasetListWidget::updateDatasetList()
{ 
 LinkedList<Dataset*> prevsel = getSelectedDatasets();
  
 FacsanaduProject* project = mw_->project();
 bool wasUpdating = isUpdating_;
 isUpdating_ = false;

 tableDatasets_->setRowCount(project->datasets().size());
 int row = 0;
 for(Dataset* ds : project->datasets() )
 {
  QTableWidgetItem* it = QTutil::createReadOnlyItem(ds->get_file_source_name());
  it->setData(Qt::ItemDataRole::UserRole, 
    QVariant::fromValue( (void*) ds) );

  tableDatasets_->setItem(row, 0, it);

  if(prevsel.contains(ds))
    it->setSelected(true);
  else
    it->setSelected(false);

  row++;
 }
 isUpdating_ = wasUpdating;
}

void DatasetListWidget::actionSelectAllDatasets()
{
 tableDatasets_->selectAll();
}

 
void DatasetListWidget::actionAddDatasets()
{
 QFileDialog dia; // =new QFileDialog();
 dia.setFileMode(QFileDialog::FileMode::ExistingFiles);
 dia.setDirectory(mw_->lastDirectory().absolutePath());
 dia.setNameFilter(tr("FCS files") + " (*.fcs *.txt *.lmd)");
 if( dia.exec() )
 {
  try
  {
   for(QString sf : dia.selectedFiles())
   {
//?    File f=new File(sf);
//?    mw.lastDirectory=f.getParentFile();
//?    mw.loadFile(f);
   }
  }
  catch ( ... ) //IOException e)
  {
   //? QTutil.showNotice(mw, e.getMessage());
   //? e.printStackTrace();
  }
 }  
 updateDatasetList();
}

void DatasetListWidget::actionRemoveDataset()
{
 FacsanaduProject* project = mw_->project();

 LinkedList<Dataset*> list = getSelectedDatasets();
 for(Dataset* ds : list)
 {
  project->datasets().removeAll(ds);
 }

 updateDatasetList();
 emitEvent(EventDatasetsChanged());
}

void DatasetListWidget::emitEvent(FacsanaduEvent event)
{
  // ptr?
 mw_->handleEvent(&event);
}


void DatasetListWidget::actionMoveUp()
{
 LinkedList<Dataset*> list = getSelectedDatasets();
 for(Dataset* ds : list)
 {
  FacsanaduProject* project = mw_->project();
  int i = project->datasets().indexOf(ds);

  if( i==0 )
    break; //Don't attempt

  project->datasets().removeAll(ds);
  project->datasets().insert(i-1, ds);
 }
 emitEvent(EventDatasetsChanged());
}
  
void DatasetListWidget::actionMoveDown()
{
 LinkedList<Dataset*> list = getSelectedDatasets();
 for(int j = list.size() - 1; j>=0; j--)
 {
  Dataset* ds = list.at(j);
  FacsanaduProject* project = mw_->project();

  int i = project->datasets().indexOf(ds);
  if(i == project->datasets().size()-1)
    break; //Don't attempt

  project->datasets().removeAll(ds);
  project->datasets().insert(i+1, ds);
 }
 emitEvent(EventDatasetsChanged());
}

LinkedList<Dataset*> DatasetListWidget::getSelectedDatasets()
{
 LinkedList<Dataset*> selviews; // = new LinkedList<Dataset>();
 for(QModelIndex in : tableDatasets_->selectionModel()->selectedRows())
 {
  selviews.append((Dataset*) tableDatasets_->item(in.row(),0)
    ->data(Qt::ItemDataRole::UserRole).value<void*>());
 }
 return selviews;
}


