
// // license___here_h


#ifndef ProfileView__H
#define ProfileView__H

#include <QPointF>
#include <QMouseEvent>
#include <QWidget>

// package facsanadu.gui.lengthprofile;


// // View showing one length profile
class ProfileView : QWidget
{
 Dataset ds_;
 MainWindow* mw_; 
 ArrayList<Integer> eventid_; // = new ArrayList<Integer>();

 QPointF pointLast_; // =new QPointF();
 int moveBoundary_; // =-1;
 
 int toViewX(int x);
 int fromViewX(int x);

 int clamp(int x, int from, int to);

public:

 bool normalizeLength_;
 ArrayList<Boolean> showchan_; //=new ArrayList<Boolean>();
 ArrayList<Double> scale_; // =new ArrayList<Double>();
 
 ProfChannel curchannel_; // =null;

 ProfileView(MainWindow mw);

protected:
 void paintEvent(QPaintEvent e) Q_DECLARE_OVERRIDE;

 void mousePressEvent(QMouseEvent event) Q_DECLARE_OVERRIDE;

 void mouseDoubleClickEvent(QMouseEvent e) Q_DECLARE_OVERRIDE;
 
 void mouseReleaseEvent(QMouseEvent ev) Q_DECLARE_OVERRIDE;
   
 void mouseMoveEvent(QMouseEvent event) Q_DECLARE_OVERRIDE;
 
public:

 void setevent(Dataset ds, int i);
 void setevent(Dataset ds, List<Integer> ids);
 
};

#endif // __H
 



