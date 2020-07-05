// package facsanadu.gui;


// //

class AddMeasureDialog : public QDialog
{
 QTableWidget* tableChannels_; //=new QTableWidget();
 QCheckBox* cbMean_; // =new QCheckBox(tr("Mean"));
 QCheckBox* cbMedian_; //=new QCheckBox(tr("Median"));
 QCheckBox* cbSD_; //=new QCheckBox(tr("Standard deviation"));
 QPushButton* bOk_; //=new QPushButton(tr("OK"));
 QPushButton* bCancel_; //=new QPushButton(tr("Cancel"));
 
 FacsanaduProject* proj;
 
 public: 

 AddMeasureDialog(FacsanaduProject proj)
 {
  this.proj=proj;
  
  tableChannels.setColumnCount(1);
  tableChannels.verticalHeader().hide();
  tableChannels.setHorizontalHeaderLabels(Arrays.asList(tr("Channel")));
  tableChannels.setSelectionBehavior(SelectionBehavior.SelectRows);
  tableChannels.horizontalHeader().setResizeMode(ResizeMode.ResizeToContents);
  tableChannels.horizontalHeader().setStretchLastSection(true);  

  bOk.clicked.connect(this,"actionOK()");
  bCancel.clicked.connect(this,"close()");
  
  updatechanlist();
  setLayout(QTutil.layoutVertical(tableChannels, cbMean, cbMedian, cbSD, QTutil.layoutHorizontal(bOk,bCancel)));
  
  setMinimumSize(200, 400);
  }

  boolean wasOK=false;
 }

 void actionOK();
  {
  wasOK=true;
  close();
  }
 
 void updatechanlist();
  {
  int row=0;
  ArrayList<ChannelInfo> chans=proj.getChannelInfo();
  tableChannels.setRowCount(chans.size());
  for(int i=0;i<chans.size();i++)
   {
   ChannelInfo ci=chans.get(i);
   QTableWidgetItem it=QTutil.createReadOnlyItem(ci.formatName());
   it.setData(Qt.ItemDataRole.UserRole, ci);
   tableChannels.setItem(row, 0, it);
   row++;
   }
  }
 
 // // Get selected channels
 LinkedList<ChannelInfo> getSelectedChannels();
  {
  LinkedList<ChannelInfo> selviews=new LinkedList<ChannelInfo>();
  for(QModelIndex in:tableChannels.selectionModel().selectedRows())
   selviews.add((ChannelInfo)tableChannels.item(in.row(),0).data(Qt.ItemDataRole.UserRole));
  return selviews;
  }
 
 Collection<GateMeasure> getMeasures();
  {
  LinkedList<GateMeasure> list=new LinkedList<GateMeasure>();
  if(wasOK)
   {
   ArrayList<ChannelInfo> chans=proj.getChannelInfo();
   for(ChannelInfo info:getSelectedChannels())
    {
    int i=chans.indexOf(info);
    if(cbMean.isChecked())
     {
     GateMeasureMean c=new GateMeasureMean();
     c.channelIndex=i;
     list.add(c);
     }
    }
   }
  return list;
  }

 
 }
