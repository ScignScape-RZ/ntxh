
// // license___here

#include "CompensationPane.h"


// package facsanadu.gui.panes;


// //

CompensationPane::CompensationPane(MainWindow* mw);
{
 mw_=mw;  
  
 QVBoxLayout lay = new QVBoxLayout();
 lay.addWidget(tableMatrix);
  //lay.addStretch();
 lay.setMargin(0);
 setLayout(lay);
 updateForm();
}
 
void CompensationPane::updateForm()
{
 updating=true;
 tableMatrix.clear();
  
 tableMatrix.horizontalHeader().setResizeMode(ResizeMode.ResizeToContents);
 tableMatrix.horizontalHeader().setStretchLastSection(true);  

 Compensation comp=mw.project.compensation;
  
 LinkedList<String> header=new LinkedList<String>();
 LinkedList<String> headerFrom=new LinkedList<String>();
 for(String s:comp.cnames)
 {
  header.add(s);
  headerFrom.add(tr("To: ")+s);
 }
  
  //ROW is TO. COL is FROM
  
 tableMatrix.setColumnCount(comp.getSize());
 tableMatrix.setRowCount(comp.getSize());
 tableMatrix.setHorizontalHeaderLabels(header);
 tableMatrix.setVerticalHeaderLabels(headerFrom);
  
 for(int row=0;row<comp.getSize();row++)
 {
  for(int col=0;col<comp.getSize();col++)
  {
   QTableWidgetItem it=new QTableWidgetItem(""+comp.get(row,col));
   it.setFlags(new ItemFlags(ItemFlag.ItemIsSelectable, ItemFlag.ItemIsEnabled,  ItemFlag.ItemIsEditable));
   tableMatrix.setItem(row, col, it);
  }
 }
 tableMatrix.itemChanged.connect(this,"dataChanged(QTableWidgetItem)");
 updating=false;
}
 
 
void CompensationPane::dataChanged(QTableWidgetItem it)
{
 if(!updating)
 {
  Compensation comp=mw.project.compensation;
  comp.set(it.row(),it.column(),Double.parseDouble(it.text()));
  mw.handleEvent(new EventCompensationChanged());
 }
}
