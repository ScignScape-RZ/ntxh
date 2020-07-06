
// // license___here_h


#ifndef QColorCombo__H
#define QColorCombo__H


// package facsanadu.gui.colors;


// // Combo box: List of colors

class QColorCombo :  QPushButton
{
 ColorSet colorset_; // = ColorSet.colorset;
 GateColor currentColor_ = colorset.get(0);
 
 int size_; // = 12;
 
 QSignalEmitter.Signal0 currentIndexChanged=new QSignalEmitter.Signal0();
 
public:

 QColorCombo();
 
 void updateColorIcon();
 static QPixmap makeColPM(GateColor col, int size);
 void setCurrentColor(GateColor c);
 GateColor getCurrentColor();
 void actionClick();
};

#endif // __H
 



