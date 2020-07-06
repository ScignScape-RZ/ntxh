
// // license___here

#include "DataetInfoPane.h"


// package facsanadu.gui.panes;



// // Pane showing metadata about a dataset

DatasetInfoPane::DatasetInfoPane(MainWindow* mw)
{
 tableMatrix_ = new QTableWidget();
 updating_ = false;
 
 mw_ = mw; 

 updateForm();
 
 QVBoxLayout* lay = new QVBoxLayout();
 lay.addWidget(tableMatrix);
 // lay.addStretch();
 lay.setMargin(0);
 setLayout(lay);
 updateForm();
}

 
void DatasetInfoPane::updateForm()
{
 updating=true;
 
 tableMatrix.clear();
 tableMatrix.verticalHeader().hide();
 
 //Columns
 LinkedList<String> header=new LinkedList<String>();
 header.add("Key");
 header.add("Value");
 tableMatrix.setColumnCount(2);
 tableMatrix.setHorizontalHeaderLabels(header);
 
 if(mw.getSelectedDatasets().size()==1)
 {
  Dataset ds=mw.getSelectedDatasets().getFirst();
  TreeMap<String, String> metaKeyName=new TreeMap<String, String>(ds.metaKeyName);
  metaKeyName.put("# observations", ""+ds.getNumObservations());
  
  
  ArrayList<String> keyw=new ArrayList<String>(metaKeyName.keySet());
  tableMatrix.setRowCount(keyw.size());

  for(int i=0;i<keyw.size();i++)
  {
   QTableWidgetItem it=new QTableWidgetItem(""+keyw.get(i));
   it.setFlags(new ItemFlags(ItemFlag.ItemIsSelectable, ItemFlag.ItemIsEnabled));
   tableMatrix.setItem(i, 0, it);

   it=new QTableWidgetItem(""+metaKeyName.get(keyw.get(i)));
   it.setFlags(new ItemFlags(ItemFlag.ItemIsSelectable, ItemFlag.ItemIsEnabled));
   tableMatrix.setItem(i, 1, it);
  }
 }
 else
 {
  tableMatrix.setRowCount(0);
 }
 
 tableMatrix.horizontalHeader().setResizeMode(ResizeMode.ResizeToContents);
 tableMatrix.horizontalHeader().setStretchLastSection(true); 
 tableMatrix.resizeColumnsToContents();
  
 tableMatrix.itemChanged.connect(this,"dataChanged(QTableWidgetItem)");
 updating=false;
}
 
 
void DatasetInfoPane::dataChanged(QTableWidgetItem it)
{
 if(!updating)
 {
 }
}


