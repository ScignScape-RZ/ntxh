
// // license___here_h


#ifndef Histogram__H
#define Histogram__H

#include <QList>
#include <QVector>


// package facsanadu.gui.view;

// //
class Histogram
{
 double from_; 
 double to_;
 int numbin_;
 QVector<int> bins_;
 int eventcount_;
 
 
public: 

 Histogram();

 void setup(double from, double to, int numbin);
 void countEvent(double x);
 double getFrom();
 double getTo();
 int getCount(int index);
 double getFrac(int index);
 int getNumBins();
};

#endif // __H
 



