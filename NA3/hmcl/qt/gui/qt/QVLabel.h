// package facsanadu.gui.qt;

// // Vertical label
class QVLabel : QWidget //extends QWidget
{
 QString text_; // ="abc";

 //@Override
protected:
 void paintEvent(QPaintEvent e);

public:

 QVLabel(QWidget parent);
 void setText(String text);

};

