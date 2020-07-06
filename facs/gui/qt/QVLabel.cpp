
// // license___here

#include "QVLabel.h"


// package facsanadu.gui.qt;

QVLabel::QVLabel(QWidget* parent) // extends QWidget
{
 text_ = "abc";

 QWidget(parent);
 setMinimumWidth(15);
}
 
void QVLabel::setText(QString text)
{
 text_ = text;
 update();
}
 
void QVLabel::paintEvent(QPaintEvent e)
{
// super.paintEvent(e);
  
 QPainter painter=new QPainter(this);
 QFontMetrics fm=new QFontMetrics(painter.font());
 QFont font=painter.font();
 font.setBold(true);
 painter.setFont(font);
 painter.setPen(QColor.black);
 painter.rotate(-90);
 painter.drawText(new QPoint(-(height()-fm.width(text))/2,11), text);
}

