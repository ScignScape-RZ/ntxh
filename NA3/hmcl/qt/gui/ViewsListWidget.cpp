
// // license___here

#include "ViewsListWidget.h"

ViewsListWidget::ViewsListWidget(MainWindow* mw)
 :  mw_(mw)
{
 main_layout_ = new QVBoxLayout;

 setMargin(0);
  
 tableViews.verticalHeader().hide();
 tableViews.setSelectionBehavior(SelectionBehavior.SelectRows);
 tableViews.horizontalHeader().setResizeMode(ResizeMode.ResizeToContents);
 tableViews.horizontalHeader().setStretchLastSection(true); 
 tableViews.selectionModel().selectionChanged.connect(this,"dothelayout()");
 
 QPushButton* bSelectAllViews = new QPushButton(tr("Select all"));
 QPushButton* bNewView = new QPushButton(tr("New view"));
 QPushButton* bRemoveView = new QPushButton(new QIcon(ImgResource.delete),"");

 bNewView.clicked.connect(this,"actionNewView()");
 bRemoveView.clicked.connect(this,"actionRemoveView()");
 bSelectAllViews.clicked.connect(this,"actionSelectAllViews()");

 main_layout_->addWidget(tableViews);
 main_layout_->addLayout(QTutil.layoutHorizontal(bSelectAllViews, bNewView, bRemoveView));

 tableViews.setSizePolicy(Policy.Minimum, Policy.Expanding);
}
 
void ViewsListWidget::dothelayout()
{
 mw.handleEvent(new EventViewsChanged()); //possible overkill?
}
 
void ViewsListWidget::actionSelectAllViews()
{
 tableViews.selectAll();
}

// // Get selected views
LinkedList<ViewSettings> ViewsListWidget::getSelectedViews()
{
 LinkedList<ViewSettings> selviews=new LinkedList<ViewSettings>();
 for(QModelIndex in : tableViews.selectionModel().selectedRows())
 {
  selviews.add((ViewSettings)tableViews.item(in.row(),0).data(Qt.ItemDataRole.UserRole));
 }
 return selviews;
}


// // Update list with views
void ViewsListWidget::updateViewsList()
{
 LinkedList<ViewSettings> selviews=getSelectedViews();
 
 FacsanaduProject project=mw.project;
 boolean wasUpdating=isUpdating;
 isUpdating=true;
 tableViews.clear(); //clears title?
 
 tableViews.setColumnCount(1);
 tableViews.setHorizontalHeaderLabels(Arrays.asList(tr("View")));

 tableViews.setRowCount(project.views.size());
 int row=0;
 for(ViewSettings vs:project.views)
 {
  String showname=vs.gate.name+": ";
  if(!project.datasets.isEmpty())
  {
   Dataset ds=project.datasets.get(0);
   if(vs.indexX==vs.indexY)
    showname+=ds.getChannelInfo().get(vs.indexX).getShortestName();
   else
    showname+=ds.getChannelInfo().get(vs.indexX).getShortestName()+" / "+ds.getChannelInfo().get(vs.indexY).getShortestName();
  }
  
  QTableWidgetItem it=QTutil.createReadOnlyItem(showname);
  it.setData(Qt.ItemDataRole.UserRole, vs);
  tableViews.setItem(row, 0, it);
  if(selviews.contains(vs))
    tableViews.selectionModel().select(tableViews.model().index(row, 0), SelectionFlag.Rows, SelectionFlag.Select);
  row++;
 }
  
 isUpdating_ = wasUpdating;
}

 

// // Action: Remove selected views
void ViewsListWidget::actionRemoveView()
{
 FacsanaduProject* project = mw_->project;
 project->views.removeAll(getSelectedViews());
 updateViewsList();
}

 
// // Action: Create a new view
void ViewsListWidget::actionNewView()
{
 FacsanaduProject* project = mw_->project;
 ViewSettings* vs = new ViewSettings();
 vs.gate=project.gateset.getRootGate();
 vs.indexX=0;
 vs.indexY=1;                                                    
 if(project.getNumChannels()>vs.indexX)
   vs.indexX=0;
 if(project.getNumChannels()>vs.indexY)
   vs.indexY=0;
 
 //autoscale here the first time?
 
 project->views.add(vs);
 updateViewsList();
}

