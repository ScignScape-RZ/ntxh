
// // license___here

#include "ViewsListWidget.h"

#include "resource/ImgResource.h"

#include "qt/QTutil.h"

#include "MainWindow.h"

#include "view/ViewSettings.h"

#include "events/FacsanaduEvent.h"

#include "FacsanaduProject.h"

#include "../gates/gate-info.h"
#include "../data/Dataset.h"
#include "../data/ChannelInfo.h"

//#include "QTutil.h"


#include <QHeaderView>

ViewsListWidget::ViewsListWidget(MainWindow* mw)
 :  mw_(mw)
{
 main_layout_ = new QVBoxLayout;

 //? main_layout_->setSpacing(0);
 
 //? setMargin(0);
  
 tableViews_->verticalHeader()->hide();
 tableViews_->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
 tableViews_->horizontalHeader()->setSectionResizeMode(
   QHeaderView::ResizeMode::ResizeToContents);
 tableViews_->horizontalHeader()->setStretchLastSection(true); 

//? tableViews_->selectionModel().selectionChanged.connect(this,"dothelayout()");
 
 QPushButton* bSelectAllViews = new QPushButton(tr("Select all"));
 QPushButton* bNewView = new QPushButton(tr("New view"));

 QPushButton* bRemoveView = new QPushButton(QIcon(ImgResource::icon_delete),"");

// bNewView.clicked.connect(this,"actionNewView()");
// bRemoveView.clicked.connect(this,"actionRemoveView()");
// bSelectAllViews.clicked.connect(this,"actionSelectAllViews()");

 main_layout_->addWidget(tableViews_);

 main_layout_->addLayout(QTutil::layoutHorizontal({bSelectAllViews, bNewView, bRemoveView}));

 tableViews_->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
}
 
void ViewsListWidget::dothelayout()
{
 mw_->handleEvent(new EventViewsChanged()); //possible overkill?
}
 
void ViewsListWidget::actionSelectAllViews()
{
 tableViews_->selectAll();
}

// // Get selected views
LinkedList<ViewSettings*> ViewsListWidget::getSelectedViews()
{
 LinkedList<ViewSettings*> selviews; // =new LinkedList<ViewSettings>();
 for(QModelIndex in : tableViews_->selectionModel()->selectedRows())
 {
  selviews.append((ViewSettings*) tableViews_->item(in.row(), 0)->data(Qt::ItemDataRole::UserRole).value<void*>());
 }
 return selviews;
}


// // Update list with views
void ViewsListWidget::updateViewsList()
{
 LinkedList<ViewSettings*> selviews = getSelectedViews();
 
 FacsanaduProject* project = mw_->project();
 bool wasUpdating = isUpdating_;
 isUpdating_ = true;
 tableViews_->clear(); //clears title?
 
 tableViews_->setColumnCount(1);
 tableViews_->setHorizontalHeaderLabels({tr("View")}); //Arrays.asList(tr("View")));

 tableViews_->setRowCount(project->views().size());

 int row = 0;

 for(ViewSettings* vs : project->views())
 {
  QString showname = vs->gate()->name() + ": ";
  if( !project->datasets().isEmpty() )
  {
   Dataset* ds = project->datasets().first();

   if(vs->indexX() == vs->indexY() )
     showname += ds->getChannelInfo().value( vs->indexX() )->getShortestName();
   else
     showname += ds->getChannelInfo().value( vs->indexX() )->getShortestName() + 
     " / " + ds->getChannelInfo().value( vs->indexY() )->getShortestName();
  }
  
  QTableWidgetItem* qtwi = QTutil::createReadOnlyItem(showname);
  qtwi->setData(Qt::ItemDataRole::UserRole, QVariant::fromValue( (void*)vs ));
  tableViews_->setItem(row, 0, qtwi);
  if(selviews.contains(vs))
    tableViews_->selectionModel()->select(tableViews_->model()->index(row, 0),
    (QItemSelectionModel::SelectionFlag::Rows |
      QItemSelectionModel::SelectionFlag::Select) );
  ++row;
 }
  
 isUpdating_ = wasUpdating;
}

 

// // Action: Remove selected views
void ViewsListWidget::actionRemoveView()
{
 FacsanaduProject* project = mw_->project();

  // //    project->views().removeAll(getSelectedViews());
 for(ViewSettings* v : getSelectedViews())
   project->views().removeAll(v);

 updateViewsList();
}

 
// // Action: Create a new view
void ViewsListWidget::actionNewView()
{
 FacsanaduProject* project = mw_->project();
 ViewSettings* vs = new ViewSettings();

 vs->gate = project->gateset() -> getRootGate();

 vs->indexX = 0;
 vs->indexY = 1;                                                    

 if(project.getNumChannels()>vs.indexX)
   vs.indexX=0;
 if(project.getNumChannels()>vs.indexY)
   vs.indexY=0;
 
 //autoscale here the first time?
 
 project->views.add(vs);
 updateViewsList();
}

