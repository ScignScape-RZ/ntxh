
// // license___here

#include "QColorComboProper.h"


// package facsanadu.gui.colors;

QColorComboProper::QColorComboProper()
{
 colorset_ = ColorSet.colorset;

 size_ = 12;

 setSizePolicy(Policy.Minimum, Policy.Minimum);
 fillColorCombo();
}
 
void QColorComboProper::fillColorCombo()
    {
  for(GateColor col:colorset.colors)
   addColor(col);
  setIconSize(new QSize(size,size));
    }

void QColorComboProper::addColor(GateColor col)
   {
   QPixmap pm=new QPixmap(size, size);
   pm.fill(new QColor(0,0,0,0));   
   QPainter p=new QPainter(pm);
   p.setBrush(new QColor(col.r,col.g,col.b));
   p.drawEllipse(1,1,size-2,size-2);
   p.end();
   addItem(new QIcon(pm), null, col);
   }
  

GateColor QColorComboProper::getCurrentColor()
   {
   return colorAt(currentIndex());
   }

GateColor QColorComboProper::colorAt(int index)
   {
  GateColor o=(GateColor)itemData(index);
  return o;
   }

void QColorComboProper::setColor(GateColor color)
  {
  for(int i=0;i<count();i++)
   {
   GateColor o=(GateColor)itemData(i);
   if(o.equals(color))
    {
    setCurrentIndex(i);
    break;
    }
   }
  addColor(color);
  setCurrentIndex(count()-1);
  }
 
