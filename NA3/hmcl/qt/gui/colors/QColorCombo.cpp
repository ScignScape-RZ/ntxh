
// // license___here

#include "QColorCombo.h"


// package facsanadu.gui.colors;


// // Combo box: List of colors
QColorCombo::QColorCombo()
{
 colorset_ = ColorSet.colorset;
 currentColor_ = colorset.get(0);
 
 size_ = 12;
 
 currentIndexChanged_ = new QSignalEmitter.Signal0();
 
 setSizePolicy(Policy.Minimum, Policy.Minimum);
 updateColorIcon();
 //fillColorCombo();
  
 clicked.connect(this,"actionClick()");
}
 
void QColorCombo::updateColorIcon()
  {
  setIcon(new QIcon(makeColPM(currentColor, size)));
  }
 

QPixmap QColorCombo::makeColPM(GateColor col, int size)
   {
   QPixmap pm=new QPixmap(size, size);
   pm.fill(new QColor(0,0,0,0));   
   QPainter p=new QPainter(pm);
   p.setBrush(new QColor(col.r,col.g,col.b));
   p.drawEllipse(1,1,size-2,size-2);
   p.end();
   return pm;
   }
  
  
void QColorCombo::setCurrentColor(GateColor c)
   {
   currentColor=c;
   updateColorIcon();
   currentIndexChanged.emit();
   }
  
GateColor QColorCombo::getCurrentColor()
{

}

void QColorCombo::actionClick()
{
 new QColorComboPopup(this, colorset);
}



