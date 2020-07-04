// package facsanadu.gui;

DatasetListWidget::DatasetListWidget(MainWindow mw*) 
 :  mw_(mw)
{ 
 main_layout_ = new QVBoxLayout;
 isUpdating_ = false;

 tableDatasets = new QTableWidget();

 selectionChanged = new QSignalEmitter.Signal0();
 
 setMargin(0);
  
 tableDatasets.setColumnCount(1);
 tableDatasets.verticalHeader().hide();
 tableDatasets.setHorizontalHeaderLabels(Arrays.asList(tr("Dataset")));
 tableDatasets.setSelectionBehavior(SelectionBehavior.SelectRows);
 tableDatasets.horizontalHeader().setResizeMode(ResizeMode.ResizeToContents);
 tableDatasets.horizontalHeader().setStretchLastSection(true);  
 tableDatasets.selectionModel().selectionChanged.connect(this,"dothelayout()");


 QPushButton bAddDataset=new QPushButton(tr("Add dataset"));
 QPushButton bSelectAllDataset=new QPushButton(tr("Select all"));
 QPushButton bRemoveDataset=new QPushButton(new QIcon(ImgResource.delete),"");
  
 QPushButton bMoveUp=new QPushButton(new QIcon(ImgResource.moveUp),"");
 QPushButton bMoveDown=new QPushButton(new QIcon(ImgResource.moveDown),"");
  
 bAddDataset.clicked.connect(this,"actionAddDatasets()");
 bRemoveDataset.clicked.connect(this,"actionRemoveDataset()");
 bSelectAllDataset.clicked.connect(this,"actionSelectAllDataset()");
 bMoveUp.clicked.connect(this,"actionMoveUp()");
 bMoveDown.clicked.connect(this,"actionMoveDown()");

 main_layout_->addWidget(tableDatasets);
 main_layout_->addLayout(QTutil.layoutHorizontal(bMoveUp, bMoveDown, bAddDataset, bSelectAllDataset, bRemoveDataset));

 tableDatasets.setSizePolicy(Policy.Minimum, Policy.Expanding);
}

void DatasetListWidget::dothelayout()
{
 selectionChanged.emit();
}
  
void DatasetListWidget::updateDatasetList()
{ 
 LinkedList<Dataset> prevsel = getSelectedDatasets();
  
 FacsanaduProject* project=mw_->project;
 bool wasUpdating=isUpdating;
 isUpdating_ = false;
 tableDatasets.setRowCount(project.datasets.size());
 int row=0;
 for(Dataset ds:project.datasets)
 {
  QTableWidgetItem it=QTutil.createReadOnlyItem(ds.source.getName());
  it.setData(Qt.ItemDataRole.UserRole, ds);
  tableDatasets.setItem(row, 0, it);
  if(prevsel.contains(ds))
    it.setSelected(true);
  else
    it.setSelected(false);
  row++;
 }
 isUpdating_ = wasUpdating;
}

 void DatasetListWidget::actionSelectAllDataset()
  {
  tableDatasets.selectAll();
  }

 
void DatasetListWidget::actionAddDatasets()
{
 QFileDialog dia=new QFileDialog();
 dia.setFileMode(FileMode.ExistingFiles);
 dia.setDirectory(mw.lastDirectory.getAbsolutePath());
 dia.setNameFilter(tr(tr("FCS files")+" (*.fcs *.txt *.lmd)"));
 if(dia.exec()!=0)
 {
  try
  {
   for(String sf:dia.selectedFiles())
   {
    File f=new File(sf);
    mw.lastDirectory=f.getParentFile();
    mw.loadFile(f);
   }
  }
  catch (IOException e)
  {
   QTutil.showNotice(mw, e.getMessage());
   e.printStackTrace();
  }
 }  
 updateDatasetList();
}

void DatasetListWidget::actionRemoveDataset()
{
 FacsanaduProject project=mw.project;
 project.datasets.removeAll(getSelectedDatasets());
 updateDatasetList();
 emitEvent(new EventDatasetsChanged());
}

void DatasetListWidget::emitEvent(FacsanaduEvent event);
{
 mw.handleEvent(event);
}


void DatasetListWidget::actionMoveUp()
{
 LinkedList<Dataset> list=getSelectedDatasets();
 for(Dataset ds:list)
 {
  FacsanaduProject project=mw.project;
  int i=project.datasets.indexOf(ds);
  if(i==0)
    break; //Don't attempt
  project.datasets.remove(ds);
  project.datasets.add(i-1, ds);
 }
 emitEvent(new EventDatasetsChanged());
}
  
void DatasetListWidget::actionMoveDown()
{
 LinkedList<Dataset> list=getSelectedDatasets();
 for(int j=list.size()-1;j>=0;j--)
 {
  Dataset ds=list.get(j);
  FacsanaduProject project=mw.project;
  int i=project.datasets.indexOf(ds);
  if(i==project.datasets.size()-1)
    break; //Don't attempt
  project.datasets.remove(ds);
  project.datasets.add(i+1, ds);
 }
 emitEvent(new EventDatasetsChanged());
}

DatasetListWidget::LinkedList<Dataset> getSelectedDatasets()
{
 LinkedList<Dataset> selviews=new LinkedList<Dataset>();
 for(QModelIndex in:tableDatasets.selectionModel().selectedRows())
 {
  selviews.add((Dataset)tableDatasets.item(in.row(),0).data(Qt.ItemDataRole.UserRole));
 }
 return selviews;
}

