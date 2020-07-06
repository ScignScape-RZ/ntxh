// // license___here

#include "ProfileChannelWidget.h"


ProfileChannelWidget::ProfileChannelWidget(MainWindow* mw)
  :  mw_(mw)
{
 setMargin(0);

 main_layout_ = new QVBoxLayout;

 isUpdating_ = false;
 tableDatasets_ = new QTableWidget;
 paneProfile_ = new ProfilePane; //
 
 tableDatasets.setColumnCount(1);
 tableDatasets.verticalHeader().hide();
 tableDatasets.setHorizontalHeaderLabels(Arrays.asList(tr("Prof.Channel")));
 tableDatasets.setSelectionBehavior(SelectionBehavior.SelectRows);
 tableDatasets.horizontalHeader().setResizeMode(ResizeMode.ResizeToContents);
 tableDatasets.horizontalHeader().setStretchLastSection(true); 
 tableDatasets.selectionModel().selectionChanged.connect(this,"dothelayout()");

 QPushButton bAddChannel=new QPushButton(tr("Create prof.channel"));
 QPushButton bRemoveDataset=new QPushButton(new QIcon(ImgResource.delete),"");
 
 bAddChannel.clicked.connect(this,"actionAddChannel()");
 bRemoveDataset.clicked.connect(this,"actionRemoveChannel()");
 tableDatasets.selectionModel().selectionChanged.connect(this,"actionSelectionChanged()");
 
 addWidget(tableDatasets);
 addLayout(QTutil.layoutHorizontal(bAddChannel, bRemoveDataset));

 tableDatasets.setSizePolicy(Policy.Minimum, Policy.Expanding);
}

void ProfileChannelWidget::dothelayout()
{
 mw.dothelayout();
}
 
 
void ProfileChannelWidget::updateChannelList()
{
 FacsanaduProject project=mw.project;
 bool wasUpdating=isUpdating;
 isUpdating = false;
 tableDatasets.setRowCount(project.profchan.size());
 int row=0;
 for(ProfChannel chan : project.profchan)
 {
  QTableWidgetItem it=QTutil.createReadOnlyItem(chan.getName());   //Maybe separate columns here
  it.setData(Qt.ItemDataRole.UserRole, chan);
  tableDatasets.setItem(row, 0, it);
  row++;
 }
 isUpdating=wasUpdating;
}

void ProfileChannelWidget::actionSelectAllDataset()
{
 tableDatasets.selectAll();
}

 
// // Action: Create channel
void ProfileChannelWidget::actionAddChannel()
{
 FacsanaduProject project=mw.project;
 for(int chid:paneProfile.getSelChans())
 {
  ProfChannel ch=new ProfChannel();
  ch.channel=chid;
  project.profchan.add(ch);
  
  updateChannelList();
  tableDatasets.selectionModel().select(tableDatasets.model().index(tableDatasets.rowCount()-1, 0), SelectionFlag.ClearAndSelect);
  mw.recalcProfChan(null);
  break; //Only create one?
 }
}

 
// // Action: Remove selected channels
void ProfileChannelWidget::actionRemoveChannel()
{
 FacsanaduProject project=mw.project;
 project.profchan.removeAll(getSelectedChannels());
 updateChannelList();
 mw.recalcProfChan(null);
}

LinkedList<ProfChannel> ProfileChannelWidget::getSelectedChannels()
{
 LinkedList<ProfChannel> selviews=new LinkedList<ProfChannel>();
 for(QModelIndex in:tableDatasets.selectionModel().selectedRows())
   selviews.add((ProfChannel)tableDatasets.item(in.row(),0).data(Qt.ItemDataRole.UserRole));
 return selviews;
}

void ProfileChannelWidget::actionSelectionChanged()
{
 ProfChannel ch=null;
 for(ProfChannel c:getSelectedChannels())
   ch=c;
 paneProfile.setCurChan(ch);
}

