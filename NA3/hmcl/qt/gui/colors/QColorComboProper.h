
// // license___here_h


#ifndef QColorComboProper__H
#define QColorComboProper__H


// package facsanadu.gui.colors;


// // Combo box: List of colors

class QColorComboProper : QComboBox
{
 ColorSet colorset_; // =ColorSet.colorset;

 int size_; // =12;
 GateColor colorAt(int index);

public:

 QColorComboProper();
 void fillColorCombo();
 void addColor(GateColor col);
 GateColor getCurrentColor();
 void setColor(GateColor color);

};


