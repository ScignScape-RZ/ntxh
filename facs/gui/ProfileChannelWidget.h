
// // license___here_h

#ifndef ProfileChannelWidget__H
#define ProfileChannelWidget__H

#include <QDialog>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QCheckBox>
#include <QPushButton>

#include <QWidget>

// // temp
#include<QList>
#define LinkedList QList

class ProfilePane;
class MainWindow;
class ProfChannel;

class ProfileChannelWidget : public QWidget // extends QVBoxLayout
{
 MainWindow* mw_;

 QVBoxLayout* main_layout_;

 bool isUpdating_; //=false;
 QTableWidget* tableDatasets_; //=new QTableWidget();
 ProfilePane* paneProfile_; //
 

public:

 ProfileChannelWidget(MainWindow* mw);

 void set_paneProfile(ProfilePane* paneProfile)
 {
  paneProfile_ = paneProfile;
 }

 void dothelayout();
 
 // // Update list with channels
 void updateChannelList();

 void actionSelectAllDataset();
 
 // // Action: Create channel
 void actionAddChannel();
 
 // // Action: Remove selected channels
 void actionRemoveChannel();


 // // Get selected channels
 LinkedList<ProfChannel*> getSelectedChannels();

 void actionSelectionChanged();

};

#endif // __H
 


