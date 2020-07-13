
// // license___here

#include "Histogram.h"


// package facsanadu.gui.view;

/**
 * 
 * One computed histogram
 * 
 * @author Johan Henriksson
 *
 */
Histogram::Histogram()
{
 //double from, to;
 //int numbin;
 //int[] bins;
 //int eventcount;
} 
 
void Histogram::setup(double from, double to, int numbin)
{
 from_ = from;
 to_ = to;
 numbin_ = numbin;
 bins_.resize(numbin);
 // bins_ = new QList<int>; //[numbin];
}
 

void Histogram::countEvent(double x)
{
 double bin = numbin_ *(x-from_)/(to_-from_);  
 if(bin >= numbin_)
 {
  bin=numbin_ - 1;
 }
 else if(bin<0)
   bin=0;
 ++bins_[(int)bin];
 ++eventcount_;
}
 
double Histogram::getFrom()
{
 return from_;
}

double Histogram::getTo()
{
 return to_;
}
 
int Histogram::getCount(int index)
{
 return bins_[index];
}

double Histogram::getFrac(int index)
{
 return getCount(index) / (double) eventcount_;
}
 
int Histogram::getNumBins()
{
 return numbin_;
}


