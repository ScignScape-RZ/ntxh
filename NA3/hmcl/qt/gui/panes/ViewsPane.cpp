
// // license___here

#include "ViewsPane.h"


// package facsanadu.gui.panes;


// //

ViewsPane::ViewsPane()
{
 spMaxEvents_ = new QSpinBox();
 cbMaxEvents_ = new QCheckBox(tr("Show max events:"));

 ViewsMatrix matrix;
 bgroup_ = new QButtonGroup(this);

 bGateSelect_ = new QPushButton(new QIcon(ImgResource.gateSelect),"");
 bGatePoly_ = new QPushButton(new QIcon(ImgResource.gatePolygon),"");
 bGateRect_ = new QPushButton(new QIcon(ImgResource.gateRect),"");
 bGateEllipse_ = new QPushButton(new QIcon(ImgResource.gateEllipse),"");
 bGateRange_ = new QPushButton(new QIcon(ImgResource.gateRange),"");
 tb=new QList<QPushButton>({bGateSelect, bGatePoly, bGateRect, bGateEllipse, bGateRange});

 matrix_ = new ViewsMatrix(mw);
  
 for(QPushButton* t : tb)
 {
  bgroup.addButton(t);
 }

 for(QPushButton* t : tb)
 {
  t.setCheckable(true);
 }

 bGateSelect.setChecked(true);
 
 for(QPushButton t:tb)
 {
  t.toggled.connect(this,"actionSetTool()");
 }
  
 spMaxEvents.setMinimum(100);
 spMaxEvents.setMaximum(10000000);
 spMaxEvents.setValue(100000);
 cbMaxEvents.setChecked(true);
  
 QHBoxLayout* laytop = new QHBoxLayout();
 
 for(QPushButton t:tb)
 {
  laytop.addWidget(t);
 }

 laytop.addStretch();
 laytop.addWidget(cbMaxEvents);
 laytop.addWidget(spMaxEvents);
 laytop.setMargin(2);
 laytop.setSpacing(2);  
  
 scrollArea = new QScrollArea();
 scrollArea.setWidgetResizable(true);
 scrollArea.setWidget(matrix);
 scrollArea.setSizePolicy(Policy.Expanding, Policy.Expanding);
 scrollArea.setVerticalScrollBarPolicy(ScrollBarPolicy.ScrollBarAlwaysOn);

 lay = new QVBoxLayout();
 lay.addLayout(laytop);
 lay.addWidget(scrollArea);
 lay.setMargin(0);
 lay.setSpacing(2);
 setLayout(lay);
  
 spMaxEvents.valueChanged.connect(this,"valuesupdated()");
 cbMaxEvents.stateChanged.connect(this,"valuesupdated()");
 valuesupdated();
}

void ViewsPane::updateViews()
{
 matrix.updateViews();
}

void ViewsPane::valuesupdated()
{
 int maxevents=Integer.MAX_VALUE;
 if(cbMaxEvents.isChecked())
   maxevents=spMaxEvents.value();
 matrix.setMaxEvents(maxevents);
}

void ViewsPane::actionSetTool()
{
 if(bgroup.checkedButton()==bGatePoly)
   setTool(ViewToolChoice.POLY);
 else if(bgroup.checkedButton()==bGateSelect)
   setTool(ViewToolChoice.SELECT);
 else if(bgroup.checkedButton()==bGateRect)
   setTool(ViewToolChoice.RECT);
 else if(bgroup.checkedButton()==bGateEllipse)
   setTool(ViewToolChoice.ELLIPSE);
 else if(bgroup.checkedButton()==bGateRange)
   setTool(ViewToolChoice.RANGE);
}

void ViewsPane::setTool(ViewToolChoice t)
{
 if(t==ViewToolChoice.SELECT)
   bGateSelect.setChecked(true);
 else if(t==ViewToolChoice.POLY)
   bGatePoly.setChecked(true);
 else if(t==ViewToolChoice.RECT)
   bGateRect.setChecked(true);
 matrix.setTool(t);
}

 
void ViewsPane::invalidateCache()
{
 matrix.invalidateCache();
}

