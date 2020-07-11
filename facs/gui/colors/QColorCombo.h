
// // license___here_h


#ifndef QColorCombo__H
#define QColorCombo__H

//
#include "../gates/gate-info.h"



#include <QPixmap>



// package facsanadu.gui.colors;

class ColorSet; // = ColorSet.colorset;
//class GateColor; // = colorset.get(0);


// // Combo box: List of colors

class QColorCombo : public QPushButton
{
 ColorSet* colorset_; // = ColorSet.colorset;
 GateColor* currentColor_; // = colorset_->get(0);
 
 int size_; // = 12;
 
 //QSignalEmitter.Signal0 currentIndexChanged=new QSignalEmitter.Signal0();
 
public:

 QColorCombo();
 
 void updateColorIcon();
 static QPixmap makeColPM(GateColor col, int size);
 void setCurrentColor(GateColor c);
 GateColor getCurrentColor();
 void actionClick();
};

#endif // __H
 



