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
 bins_ = new QList<int>; //[numbin];
}
 

void Histogram::countEvent(double x)
{
 double bin = numbin*(x-from)/(to-from);  
 if(bin >= numbin)
 {
  bin=numbin-1;
 }
 else if(bin<0)
   bin=0;
 bins[(int)bin]++;
 eventcount++;
}
 
double Histogram::getFrom()
{
 return from;
}

double Histogram::getTo()
{
 return to;
}
 
int Histogram::getCount(int index)
{
 return bins[index];
}

double Histogram::getFrac(int index)
{
 return getCount(index) / (double)eventcount;
}
 
int Histogram::getNumBins()
{
 return numbin;
}


