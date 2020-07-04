
GatesListWidget::GatesListWidget(MainWindow* mw) 
 : mw_(mw)
{
 main_layout_ = new QVBoxLayout;

 setMargin(0);
 
 treeGates->setHeaderLabels(Arrays.asList(tr("Gate"),tr("Color")));
 treeGates->setSelectionBehavior(SelectionBehavior::SelectRows);
 treeGates->setSelectionMode(SelectionMode::MultiSelection);
 //?treeGates->selectionModel().selectionChanged.connect(this,"dothelayout()"); 
 treeGates->setSizePolicy(Policy::Minimum, Policy::Expanding);

 QPushButton* bSelectAllGates = new QPushButton(tr("Select all"));
 QPushButton* bRenameGate = new QPushButton(tr("Rename gate"));
 QPushButton* bRemoveGate = new QPushButton(new QIcon(ImgResource.delete),"");
 QPushButton* bMeasure = new QPushButton(tr("Measure"));

// bMeasure.clicked.connect(this,"actionAddMeasure()");
// bRenameGate.clicked.connect(this,"actionRenameGate()");
// bRemoveGate.clicked.connect(this,"actionRemoveGates()");
// bSelectAllGates.clicked.connect(this,"actionSelectAllGates()");

 main_layout_->addWidget(treeGates);
 main_layout_->addLayout(QTutil.layoutHorizontal(bMeasure, bSelectAllGates, bRenameGate, bRemoveGate));
}
 
void GatesListWidget::dothelayout()
{
 mw.dothelayout();
}
 
void GatesListWidget::actionSelectAllGates()
{
 treeGates->selectAll();
}

Gate* GatesListWidget::getCurrentGate()
{
 QTreeWidgetItem it=treeGates->currentItem();
 if(it!=null)
   return (Gate)it.data(0,Qt.ItemDataRole.UserRole);
 else
   return null;
}
 
LinkedList<Gate> GatesListWidget::getSelectedGates()
{
 LinkedList<Gate> selviews = new LinkedList<Gate*>();
 for(QTreeWidgetItem* it : treeGates->selectedItems())
 {
  Object* ob = it.data(0,Qt.ItemDataRole.UserRole);
  if(ob instanceof Gate)
    selviews.add((Gate)ob);
 }
 return selviews;
}

LinkedList<GateMeasure> GatesListWidget::getSelectedMeasures()
{
 LinkedList<GateMeasure> selviews = new LinkedList<GateMeasure>();
 for(QTreeWidgetItem it:treeGates->selectedItems())
 {
  Object ob = it.data(0, Qt.ItemDataRole.UserRole);
  if(ob instanceof GateMeasure)
    selviews.add((GateMeasure)ob);
  }
 return selviews;
}
  
void GatesListWidget::updateGatesList()
 {
 boolean wasUpdating=isUpdating;
 callbacks.clear();
 LinkedList<Gate> selgates=getSelectedGates();
 LinkedList<GateMeasure> selcalc=getSelectedMeasures();
 isUpdating=false;
 treeGates->clear();
 updateGatesListRecursive(null, mw.project.gateset.getRootGate(), selgates, selcalc);
 treeGates->expandAll();

 treeGates->resizeColumnToContents(0);
 
 isUpdating=wasUpdating;
 }

void GatesListWidget::updateGatesListRecursive(QTreeWidgetItem parentItem, final Gate g, LinkedList<Gate> selgates, LinkedList<GateMeasure> selcalc)
{
 QTreeWidgetItem* item;

 if(parentItem==null)
   item=new QTreeWidgetItem(treeGates);
 else
   item=new QTreeWidgetItem(parentItem);

 item.setData(0,Qt.ItemDataRole.UserRole, g);
 item.setText(0, g.name+"   "); //spacing, can we do better?
 final QColorCombo combocolor=new QColorCombo();
 treeGates->setItemWidget(item, 1, combocolor);
 combocolor.setCurrentColor(g.color);

 CallbackColor cb=new CallbackColor()
 {
  void set()
  {
   g.color=combocolor.getCurrentColor();
   emitEvent(new EventGatesChanged()); //Smaller change?
  }
 };

 this.callbacks.add(cb);
 combocolor.currentIndexChanged.connect(cb,"set()");
 
 if(selgates.contains(g))
  item.setSelected(true);
 
 addMeasures(item, g, selcalc);
 
 for(Gate child:g.children)
 {
  updateGatesListRecursive(item, child, selgates, selcalc);
 }
}

void GatesListWidget::addMeasures(QTreeWidgetItem parentItem, Gate g, LinkedList<GateMeasure> selcalc)
{
 for(GateMeasure calc:g.getMeasures())
 {
  QTreeWidgetItem* item;
  if(parentItem == null)
    item = new QTreeWidgetItem(treeGates);
  else
    item = new QTreeWidgetItem(parentItem);
  item->setData(0, Qt.ItemDataRole.UserRole, calc); 
    //g and calc needed here. or get parent?
  item->setText(0, calc.getDesc(mw.project));

  if(selcalc.contains(g))
    item.setSelected(true);
 } 
}

void GatesListWidget::actionAddMeasure()
{
 LinkedList<Gate> gates=getSelectedGates();
 if(gates.isEmpty())
   QTutil.showNotice(mw, tr("First select some gates"));
 else
 {
  AddMeasureDialog* w = new AddMeasureDialog(mw.project);
  w.exec();
  
  for(Gate g:gates)
  {
   for(GateMeasure calc : w.getMeasures())
   {
    g.attachMeasure(calc);
   }
   emitEvent(new EventGatesChanged()); 
  }
 }
}
 
void GatesListWidget::actionRenameGate()
{
 FacsanaduProject project = mw.project;

 Gate g=getCurrentGate();

 if( (g != nullptr) && (g != project.gateset.getRootGate()) )
 {
  String newname = QInputDialog::getText(mw, tr("Rename gate"), tr("New name:"), EchoMode.Normal, g.name);

  if(!newname.equals("") && (newname.equals(g.name) || !project.gateset.getGateNames().contains(newname)))
  {
   g.name=newname;
   emitEvent(new EventGatesChanged());
  }
  else
    QTutil.showNotice(mw, tr("Invalid name"));
 } 
}


void GatesListWidget::emitEvent(FacsanaduEvent event)
{
 mw.handleEvent(event);
}

 
void GatesListWidget::actionRemoveGates()
{
 FacsanaduProject project=mw.project;

 Collection<Gate> gates = getSelectedGates();
 Collection<GateMeasure> calcs = getSelectedMeasures();

 gates.remove(project.gateset.getRootGate());
 //Should include gates recursively!

 //Needed for now - but should maybe not have updated times on individual gates
 project.gateset.getRootGate().setUpdated();
 
 for(Gate g:gates)
 {
  g.detachParent();
 }
 
 for(GateMeasure calc:calcs)
 {
  calc.detachFromGate();
 }

 bool changedViews=false;

 for(ViewSettings vs : new LinkedList<ViewSettings>(project.views))
 {
  if(gates.contains(vs.gate) || gates.contains(vs.gate.children)) 
     //TODO or any gate below!!  contains - is this AND or OR?
  {
   project.views.remove(vs);
   changedViews=true;
  }
 }
 emitEvent(new EventGatesChanged());
 if(changedViews)
   emitEvent(new EventViewsChanged());
}
 
void GatesListWidget::addGate(Gate suggestParent, Gate g)
{
 FacsanaduProject project=mw.project;
 g.name=project.gateset.getFreeName();
 Gate parent=getCurrentGate();

 if(parent==null)
   parent=project.gateset.getRootGate();
 
 //It need be a gate beneath the suggested parent!
 if(suggestParent!=null)
 {
  if(!suggestParent.children.contains(parent))
    parent=suggestParent;
 }

 System.out.println("attaching to parent: "+parent);
 parent.attachChild(g);
 
 updateGatesList();
}

