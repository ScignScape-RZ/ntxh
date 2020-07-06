
// // license___here_h


#ifndef ProfilePane__H
#define ProfilePane__H


// package facsanadu.gui.lengthprofile;

/**
 * 
 * Pane showing length profiles
 * 
 * @author Johan Henriksson
 *
 */
class ProfilePane // extends QWidget
{
 QPushButton* bPrevProf_; //= new QPushButton(new QIcon(ImgResource.moveLeft), "");
 QPushButton* bNextProf_; //= QPushButton(new QIcon(ImgResource.moveRight), "");
 QLineEdit* tfID_; //= QLineEdit("0");
 QCheckBox* cbNormalizeLength_; //= QCheckBox();
 QCheckBox* cbShowAll_; //= QCheckBox();
 
 ProfileView* view_;
 MainWindow* mw_;
 
 QGridLayout* laychans_; //= QGridLayout();
 LinkedList<QCheckBox>* cbShowChannel_; //= LinkedList<QCheckBox>();
 LinkedList<QSlider>* sScaleChannel_; //= LinkedList<QSlider>();
 
public:

 ProfilePane(MainWindow mw);

 void cbNormalizeLength();
 Gate* getCurrentGate();
 void actionPrevProf();
 void actionNextProf();
 List<Integer>* getAllFromGate();
 
 void setEventID(int id);
 Dataset* getCurrentDataset()
 int getCurrentID();
 void updateViews();
 ArrayList<Integer> getSelChans();
 void setCurChan(ProfChannel pc);

};

#endif // __H
 


