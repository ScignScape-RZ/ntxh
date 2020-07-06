
// // license___here

#include "ProfilePane.h"


// package facsanadu.gui.lengthprofile;

ProfilePane::ProfilePane()
{
 bPrevProf_ = new QPushButton(new QIcon(ImgResource.moveLeft), "");
 bNextProf_ = QPushButton(new QIcon(ImgResource.moveRight), "");
 tfID_ = QLineEdit("0");
 cbNormalizeLength_ = QCheckBox();
 cbShowAll_ = QCheckBox();
  
 QGridLayout* laychans_ = QGridLayout();
 LinkedList<QCheckBox>* cbShowChannel_ = LinkedList<QCheckBox>();
 LinkedList<QSlider>* sScaleChannel_ = LinkedList<QSlider>();

 mw_ = mw;
 view_ = new ProfileView(mw);
  
 tfID.setValidator(new QIntValidator(this));
 tfID.setMaximumWidth(100);
  
 for(int i=0;i<10;i++)
 {
  QCheckBox cb=new QCheckBox();
  cb.stateChanged.connect(this,"updateViews()");
  cb.setChecked(true);
  cbShowChannel.add(cb);
  laychans.addWidget(cb,i,0);
   
  QSlider s=new QSlider();
  s.setOrientation(Orientation.Horizontal);
  s.setMaximum(10000);
  s.setValue(2000);
  laychans.addWidget(s, i, 1);
  sScaleChannel.add(s);
  s.sliderMoved.connect(this,"updateViews()");
 }

 QHBoxLayout blay=new QHBoxLayout();
 blay.addWidget(new QLabel(tr("Show all")));
 blay.addWidget(cbShowAll);
 blay.addWidget(new QLabel(tr("Normalize length")));
 blay.addWidget(cbNormalizeLength);
 blay.addStretch();
 blay.addWidget(new QLabel(tr("Event ID:")));
 blay.addWidget(tfID);
 blay.addWidget(bPrevProf);
 blay.addWidget(bNextProf);
  
 QVBoxLayout lay=new QVBoxLayout();
 lay.addLayout(blay);
 lay.addWidget(view);
 lay.addLayout(laychans);
 
 tfID.editingFinished.connect(this,"updateViews()");
 bNextProf.clicked.connect(this,"actionNextProf()");
 bPrevProf.clicked.connect(this,"actionPrevProf()");
 cbNormalizeLength.stateChanged.connect(this,"cbNormalizeLength()");
 cbShowAll.stateChanged.connect(this,"updateViews()");
 
 setLayout(lay);
}

void ProfilePane::cbNormalizeLength()
  {
  if(view.curchannel!=null)
   view.curchannel.forNormalized=cbNormalizeLength.isChecked();
  updateViews();
  }
 
 
Gate* ProfilePane::getCurrentGate()
  {
  List<Gate> gates=mw.getSelectedGates();
  Gate g;
  if(gates.isEmpty())
   g=mw.project.gateset.getRootGate();
  else
   g=gates.get(0);
  return g;
  }
 
void ProfilePane::actionPrevProf()
  {
  int id=getCurrentID();
  Dataset ds=getCurrentDataset();
  if(ds!=null)
   {
   GatingResult gres=mw.project.getGatingResult(ds);
   IntArray arr=gres.getAcceptedFromGate(getCurrentGate());
   for(int i=arr.size()-1;i>=0;i--)
    if(arr.get(i)<id)
     {
     setEventID(arr.get(i));
     break;
     }
   }
  }

void ProfilePane::actionNextProf()
  {
  int id=getCurrentID();
  Dataset ds=getCurrentDataset();
  if(ds!=null)
   {
   GatingResult gres=mw.project.getGatingResult(ds);
   IntArray arr=gres.getAcceptedFromGate(getCurrentGate());
   for(int i=0;i<arr.size();i++)
    if(arr.get(i)>id)
     {
     setEventID(arr.get(i));
     break;
     }
   }
  }

List<Integer> ProfilePane::getAllFromGate()
  {
  Dataset ds=getCurrentDataset();
  if(ds!=null)
   {
   GatingResult gres=mw.project.getGatingResult(ds);
   IntArray arr=gres.getAcceptedFromGate(getCurrentGate());
   ArrayList<Integer> list=new ArrayList<Integer>(arr.size());
   for(int i=0;i<arr.size();i++)
    list.add(arr.get(i));
   return list;
   }
  else
   return new ArrayList<Integer>();
  }
 
void ProfilePane::setEventID(int id)
  {
  tfID.setText(""+id);
  updateViews();
  }
 
Dataset ProfilePane::getCurrentDataset()
  {
  List<Dataset> listds=mw.getSelectedDatasets();
  if(!listds.isEmpty())
   return listds.get(0);
  else
   return null;
  }

int ProfilePane::getCurrentID()
  {
  int id=-1;
  try
   {
   id=Integer.parseInt(tfID.text());
   }
  catch (NumberFormatException e)
   {
   e.printStackTrace();
   }
  return id;
  }
 
void ProfilePane::updateViews()
  {
  Dataset ds=getCurrentDataset();
  if(ds!=null)
   {
   ArrayList<Boolean> showchan=new ArrayList<Boolean>();
   ArrayList<Double> scale=new ArrayList<Double>();
   for(int i=0;i<ds.getNumLengthProfiles();i++)
    {
    showchan.add(cbShowChannel.get(i).isChecked());
    double pos=sScaleChannel.get(i).value()/1000.0;
    scale.add(pos/400000.0);
    }
   view.showchan=showchan;
   view.scale=scale;
   view.normalizeLength=cbNormalizeLength.isChecked();
   if(cbShowAll.isChecked())
    {
    view.setevent(ds, getAllFromGate());
    }
   else
    {
    int id=getCurrentID();
    view.setevent(ds, id);
    }
   }
  else
   {
   view.setevent(null, 0);
   ds=new Dataset();
   }
  
  //Update name and visibility of checkboxes for channels
  for(int i=0;i<cbShowChannel.size();i++)
   {
   QCheckBox cb=cbShowChannel.get(i);
   QSlider s=sScaleChannel.get(i);
   boolean visible=i<ds.lengthprofsInfo.size();
   cb.setVisible(visible);
   s.setVisible(visible);
   if(visible)
    cb.setText(ds.lengthprofsInfo.get(i).name);
   }
   

  }
 
 
ArrayList<Integer> ProfilePane::getSelChans()
  {
  Dataset ds=getCurrentDataset();
  ArrayList<Integer> showchan=new ArrayList<Integer>();
  if(ds!=null)
   for(int i=0;i<ds.getNumLengthProfiles();i++)
    {
    if(cbShowChannel.get(i).isChecked())
     showchan.add(i);
    }
  return showchan;
  }
 
 
void ProfilePane::setCurChan(ProfChannel pc)
  {
  view.curchannel=pc;
  view.repaint();
  }


