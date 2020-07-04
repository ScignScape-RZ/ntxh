
class ProfileChannelWidget extends QVBoxLayout
{
 QVBoxLayout* main_layout_;

 QVBoxLayout* main_layout_;
 bool isUpdating_; //=false;
 QTableWidget* tableDatasets_; //=new QTableWidget();
 ProfilePane* paneProfile_; //
 

public:

 ProfileChannelWidget(MainWindow* mw);

 void dothelayout();
 
 // // Update list with channels
 void updateChannelList();

 void actionSelectAllDataset();
 
 // // Action: Create channel
 void actionAddChannel();
 
 // // Action: Remove selected channels
 void actionRemoveChannel();


 // // Get selected channels
 LinkedList<ProfChannel> getSelectedChannels();

 void actionSelectionChanged();

};

