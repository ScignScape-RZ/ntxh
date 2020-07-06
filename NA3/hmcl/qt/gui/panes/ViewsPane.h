
// // license___here_h


#ifndef ViewsPane__H
#define ViewsPane__H


// package facsanadu.gui.panes;


// //
class ViewsPane :  QWidget
{
 QSpinBox* spMaxEvents_; // =new QSpinBox();
 QCheckBox* cbMaxEvents_; // =new QCheckBox(tr("Show max events:"));

 ViewsMatrix* matrix_;

 QButtonGroup* bgroup_; //  =new QButtonGroup(this);

 QPushButton* bGateSelect_; // =new QPushButton(new QIcon(ImgResource.gateSelect),"");
 QPushButton* bGatePoly_; // =new QPushButton(new QIcon(ImgResource.gatePolygon),"");
 QPushButton* bGateRect_; // =new QPushButton(new QIcon(ImgResource.gateRect),"");
 QPushButton* bGateEllipse_; // =new QPushButton(new QIcon(ImgResource.gateEllipse),"");
 QPushButton* bGateRange_; // =new QPushButton(new QIcon(ImgResource.gateRange),"");
 
 QList<QPushButton*> tb_; // =new QPushButton[]{bGateSelect, bGatePoly, bGateRect, bGateEllipse, bGateRange};

#endif // __H
 



public: 

 ViewsPane(MainWindow* mw);

 void updateViews();
 void valuesupdated();
 void actionSetTool();
 void setTool(ViewToolChoice t);
 void invalidateCache();
};


