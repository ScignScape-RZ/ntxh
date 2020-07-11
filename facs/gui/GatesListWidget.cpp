// // license___here

#include "GatesListWidget.h"



#include "qt/QTutil.h"

#include "resource/ImgResource.h"

#include "../gates/gate-info.h"
#include "../gates/GateSet.h"
#include "../gates/measure/GateMeasure.h"

#include "view/ViewSettings.h"

#include "colors/QColorCombo.h"

#include "MainWindow.h"
#include "AddMeasureDialog.h"

#include "FacsanaduProject.h"

#include "events/FacsanaduEvent.h"


#include <QInputDialog>


#define connect_this(x, y, z) connect(y, &x, \
   this, &GatesListWidget::z);



GatesListWidget::GatesListWidget(MainWindow* mw) 
 : mw_(mw)
{
 main_layout_ = new QVBoxLayout;

 //setMargin(0);
 
 treeGates_->setHeaderLabels( {tr("Gate"), tr("Color") } );

 treeGates_->setSelectionBehavior(
   QAbstractItemView::SelectionBehavior::SelectRows);

 treeGates_->setSelectionMode(
   QAbstractItemView::SelectionMode::MultiSelection);

 //?treeGates->selectionModel().selectionChanged.connect(this,"dothelayout()"); 

 connect_this(QItemSelectionModel ::selectionChanged 
   ,treeGates_->selectionModel() ,dothelayout) 


 treeGates_->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);

 QPushButton* bSelectAllGates = new QPushButton(tr("Select all"), this);
 QPushButton* bRenameGate = new QPushButton(tr("Rename gate"), this);
 QPushButton* bRemoveGate = new QPushButton(QIcon(ImgResource::icon_delete),
   "", this);
 QPushButton* bMeasure = new QPushButton(tr("Measure"), this);

 connect_this(QPushButton ::clicked ,bMeasure ,actionAddMeasure) 
 connect_this(QPushButton ::clicked ,bRenameGate ,actionRenameGate) 
 connect_this(QPushButton ::clicked ,bRemoveGate ,actionRemoveGates) 
 connect_this(QPushButton ::clicked ,bSelectAllGates ,actionSelectAllGates) 

// bMeasure.clicked.connect(this,"actionAddMeasure()");
// bRenameGate.clicked.connect(this,"actionRenameGate()");
// bRemoveGate.clicked.connect(this,"actionRemoveGates()");
// bSelectAllGates.clicked.connect(this,"actionSelectAllGates()");

 main_layout_->addWidget(treeGates_);

 main_layout_->addLayout(QTutil::layoutHorizontal(
   { bMeasure, bSelectAllGates, bRenameGate, bRemoveGate } ));
}
 
void GatesListWidget::dothelayout()
{
 mw_->dothelayout();
}
 
void GatesListWidget::actionSelectAllGates()
{
 treeGates_->selectAll();
}

Gate* GatesListWidget::getCurrentGate()
{
 QTreeWidgetItem* qtwi = treeGates_->currentItem();
 if(qtwi)
   return (Gate*) qtwi->data(0, Qt::ItemDataRole::UserRole).value<void*>();
 else
   return nullptr;
}
 
LinkedList<Gate*> GatesListWidget::getSelectedGates()
{
 LinkedList<Gate*> selviews; // = new LinkedList<Gate*>();
 for(QTreeWidgetItem* qtwi : treeGates_->selectedItems())
 {
  QObject* obj = qtwi->data(0, Qt::ItemDataRole::UserRole)
    .value<QObject*>();

  if(Gate* g = qobject_cast<Gate*>(obj) )
    selviews.append(g);
 }
 return selviews;
}

LinkedList<GateMeasure*> GatesListWidget::getSelectedMeasures()
{
 LinkedList<GateMeasure*> selviews; // = new LinkedList<GateMeasure>();

 for(QTreeWidgetItem* qtwi : treeGates_->selectedItems())
 {
  QObject* obj = qtwi->data(0, Qt::ItemDataRole::UserRole).value<QObject*>();

  if(GateMeasure* gm = qobject_cast<GateMeasure*>(obj) )
    selviews.append(gm);
 }
 return selviews;
}
  
void GatesListWidget::updateGatesList()
{
 bool wasUpdating = isUpdating_;

 callbacks_.clear();
 LinkedList<Gate*> selgates = getSelectedGates();
 LinkedList<GateMeasure*> selcalc = getSelectedMeasures();
 isUpdating_ = false;

 treeGates_->clear();

//? updateGatesListRecursive(nullptr, mw_->project()->gateset.getRootGate(), selgates, selcalc);

 treeGates_->expandAll();

 treeGates_->resizeColumnToContents(0);
 
 isUpdating_ = wasUpdating;
}

void GatesListWidget::updateGatesListRecursive(QTreeWidgetItem* parentItem, 
  const Gate* g, LinkedList<Gate*> selgates, 
  LinkedList<GateMeasure*> selcalc)
{
 QTreeWidgetItem* item;

 if(parentItem == nullptr)
   item = new QTreeWidgetItem(treeGates_);

 else
   item = new QTreeWidgetItem(parentItem);

 item->setData(0, Qt::ItemDataRole::UserRole, QVariant::fromValue(g) );
 item->setText(0, g->name() + "   "); //spacing, can we do better?

 QColorCombo* combocolor = new QColorCombo();
 treeGates_->setItemWidget(item, 1, combocolor);
 combocolor->setCurrentColor(g->color());

/*
 CallbackColor cb=new CallbackColor()
 {
  void set()
  {
   g.color=combocolor.getCurrentColor();
   emitEvent(new EventGatesChanged()); //Smaller change?
  }
 };
*/

 //?this->callbacks.append(cb);
 //?combocolor.currentIndexChanged.connect(cb,"set()");
 
 if(selgates.contains( (Gate*) g))
   item->setSelected(true);
 
 addMeasures(item, (Gate*) g, selcalc);
 
 for(Gate* child : g->children() )
 {
  updateGatesListRecursive(item, child, selgates, selcalc);
 }
}

void GatesListWidget::addMeasures(QTreeWidgetItem* parentItem, Gate* g, LinkedList<GateMeasure*> selcalc)
{
 for(GateMeasure* calc : g->getMeasures())
 {
  QTreeWidgetItem* item;
  if(parentItem == nullptr)
    item = new QTreeWidgetItem(treeGates_);
  else
    item = new QTreeWidgetItem(parentItem);

  item->setData(0, Qt::ItemDataRole::UserRole, QVariant::fromValue(calc) ); 
    //g and calc needed here. or get parent?

  //?
  item->setText(0, calc->getDesc(mw_->project() ));
  
  // //?  Should this be calc or g? 
   //if(selcalc.contains(g))
  if(selcalc.contains(calc))
    item->setSelected(true);
 } 
}

void GatesListWidget::actionAddMeasure()
{
 LinkedList<Gate*> gates = getSelectedGates();
 if(gates.isEmpty())
   QTutil::showNotice(*mw_, tr("First select some gates"));
 else
 {
  AddMeasureDialog* w = new AddMeasureDialog(mw_->project());
  w->exec();
  
  for(Gate* g : gates)
  {
   for(GateMeasure* calc : w->getMeasures() )
   {
    g->attachMeasure(calc);
   }
   emitEvent(EventGatesChanged()); 
  }
 }
}
 
void GatesListWidget::actionRenameGate()
{
 FacsanaduProject* project = mw_->project();

 Gate* g = getCurrentGate();

 if( (g != nullptr) && (g != project->gateset()->getRootGate()) )
 {
  QString newname = QInputDialog::getText(mw_, tr("Rename gate"), tr("New name:"), QLineEdit::EchoMode::Normal, g->name() );

  if( !newname.isEmpty() && ( (newname == g->name() ) 
    || !project->gateset()->getGateNames().contains(newname)))
  {
   g->set_name(newname);
   emitEvent(EventGatesChanged());
  }
  else
    QTutil::showNotice(*mw_, tr("Invalid name"));
 } 
}


void GatesListWidget::emitEvent(FacsanaduEvent event)
{
  // //  by-value?
 mw_->handleEvent(&event);
}

 
void GatesListWidget::actionRemoveGates()
{
 FacsanaduProject* project = mw_->project();

 QList<Gate*> gates = getSelectedGates();
 QList<GateMeasure*> calcs = getSelectedMeasures();

 gates.removeAll(project->gateset()->getRootGate());
 //Should include gates recursively!

 //Needed for now - but should maybe not have updated times on individual gates
 project->gateset()->getRootGate()->setUpdated();
 
 for(Gate* g : gates)
 {
  g->detachParent();
 }
 
 for(GateMeasure* calc : calcs)
 {
  calc->detachFromGate();
 }

 bool changedViews = false;

 for(ViewSettings* vs : project->views()) 
    // : new LinkedList<ViewSettings>(project.views))
 {
  if(gates.contains(vs->gate() )) 
       //?  || gates.contains(vs->gate()->children() )) 
     //TODO or any gate below!!  contains - is this AND or OR?
  {
   project->views().removeAll(vs);
   changedViews = true;
  }
 }
 emitEvent(EventGatesChanged());
 if(changedViews)
   emitEvent(EventViewsChanged());
}
 
void GatesListWidget::addGate(Gate* suggestParent, Gate* g)
{
 FacsanaduProject* project = mw_->project();
 g->set_name( project->gateset()->getFreeName() );

 Gate* parent = getCurrentGate();

 if(parent == nullptr)
   parent = project->gateset()->getRootGate();
 
 //It need be a gate beneath the suggested parent!
 if(suggestParent)
 {
  if(!suggestParent->children().contains(parent))
    parent=suggestParent;
 }

 //System.out.println("attaching to parent: "+parent);
 parent->attachChild(g);
 
 updateGatesList();
}

