// package facsanadu.gui.view;

// //
class Histogram
{
 double from_; 
 double to_;
 int numbin_;
 QList<int> bins_;
 int eventcount_;
 
 
public: 

 void setup(double from, double to, int numbin);
 void countEvent(double x);
 double getFrom();
 double getTo();
 int getCount(int index);
 double getFrac(int index);
 int getNumBins();
};


