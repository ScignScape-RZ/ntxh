// package facsanadu.gui.view;

/**
 * 
 * Settings for a view
 * 
 * @author Johan Henriksson
 *
 */
ViewSettings::ViewSettings()
{
 //Which gate the view should pick data from
 //Gate gate;
 
 indexX_ = 7;
 indexY_ = 6;
 
 //FCS space * scale = screen space (almost)
 scaleX_ = 1;
 scaleY_ = 1;
 
 zoomX_ = 1; //For speed, this is integrated into the scale whenever needed
 zoomY_ = 1;

 transformation_ = new TransformationStack();

 numHistBins_ = 50;
}
 
 /**
  * Set the scale to cover the given max and min values
  */

void ViewSettings::autoscale(double[] max, double[] min)
{
 //Currently min values are not used
 double maxx = max[indexX];
 double maxy = max[indexY];
 scaleX_ = 1.0/maxx*zoomX;
 scaleY_ = 1.0/maxy*zoomY;
} 


 /**
  * Get the maximum for a channel
  */
QList<double> ViewSettings::getMaxForChannel(Dataset dataset)
{
 QList<double> val = new QList<double> //?[dataset.getNumChannels()];
 for(int i=0;i<val.length;i++)
 {
  val[i]=-Double.MAX_VALUE;
 }
 for(int i=0;i<dataset.getNumObservations();i++)
 {
  for(int j=0;j<val.length;j++)
  {
   val[j]=Math.max(val[j],dataset.getAsFloatCompensated(i,j));
  }
 }
 val = transformation.perform(val);
 return val;
}

 /**
  * Get the minimum value for channel
  */
QList<double> ViewSettings::getMinForChannel(Dataset dataset)
{
 QList<double> val = new QList<double>; //[dataset.getNumChannels()];
 for(int i=0;i<val.length;i++)
   val[i]=Double.MAX_VALUE;

 for(int i=0;i<dataset.getNumObservations();i++)
 {
  for(int j=0;j<val.length;j++)
  {
   val[j]=Math.min(val[j],dataset.getAsFloatCompensated(i,j));
  }
 }
 val = transformation.perform(val); //this is kind of cheating
 return val;
}

 /**
  * Get the maximum value for all channels
  */
QList<double> ViewSettings::getMaxForChannels(Collection<Dataset> dataset)
{
 if(dataset.size()==0)
   return new QList<double>(0);
 else
 {
  int numchan=dataset.iterator().next().getNumChannels();
   
  QList<double> val = new QList<double>; // [numchan];
  for(int i=0;i<val.length;i++)
  {
   val[i]=-Double.MAX_VALUE;
  }
  for(Dataset ds : dataset)
  {
   QList<double> cmax = getMaxForChannel(ds);
   for(int j=0;j<numchan;j++)
   {
    val[j]=Math.max(val[j],cmax[j]);
   }
  }
  return val;
 }
}
 
 /**
  * Get the minimum value for all channels
  */
QList<double> ViewSettings::getMinForChannels(Collection<Dataset> dataset)
{
 if(dataset.size()==0)
   return new double[0];
 else
 {
  int numchan=dataset.iterator().next().getNumChannels();
   
  QList<double> val = new QList<double>; //[numchan];
  for(int i=0;i<val.length;i++)
  {
   val[i]=Double.MAX_VALUE;
  }
  for(Dataset ds:dataset)
  {
   QList<double> cmax = getMinForChannel(ds);
   for(int j=0;j<numchan;j++)
   {
    val[j]=Math.min(val[j],cmax[j]);
   }
  }
  return val;
 }
}

 /**
  * Autoscale several views according to several datasets
  */
static void ViewSettings::autoscale(LinkedList<Dataset> selds, LinkedList<ViewSettings> selviews)
{
 if(!selds.isEmpty())
 {
  for(ViewSettings vs:selviews)
  {
   //Might be possible to optimize this if there are many different kind of views
   QList<double> max = vs.getMaxForChannels(selds);
   QList<double> min = vs.getMinForChannels(selds);
   vs.autoscale(max,min);
  }
 }
}

 /**
  * Get the name of this view
  */
QString ViewSettings::getName()
{
 //Use gate name as name of view
 return gate.name;
}


 /**
  * Compute histogram from data
  */
Histogram ViewSettings::computeHistogram(Dataset data, GatingResult gr)
{
 Histogram h = new Histogram();
 h.setup(0, 1.0/scaleX, numHistBins);
 IntArray accepted=gr.getAcceptedFromGate(gate);
 if(accepted!=null)
 {
  for(int i=0;i<accepted.size();i++)
  {
   int ind=accepted.get(i);
   double x=transformation.perform(data.getAsFloatCompensated(ind, indexX), indexX);
   h.countEvent(x);
  }
 }
 return h;
}


 /**
  * Check if the view settings is for a histogram
  */
bool ViewSettings::isHistogram()
{
 return indexX==indexY;
}


void ViewSettings::setHistogram(int chanid)
{
 indexX=indexY=chanid;
}


bool ViewSettings::coversXandY(int indexX2, int indexY2)
{
 HashSet<Integer> ind=new HashSet<Integer>();
 ind.add(indexX);
 ind.add(indexY);
 return ind.contains(indexX2) && ind.contains(indexY2);
}

bool ViewSettings::coversX(int indexX2)
{
 HashSet<Integer> ind = new HashSet<Integer>();
 ind.add(indexX);
 ind.add(indexY);
 return ind.contains(indexX2);
}


void ViewSettings::swapAxis()
{
 int axis=indexX;
 indexX=indexY;
 indexY=axis;
 
 double scale=scaleX;
 scaleX=scaleY;
 scaleY=scale;
  
 double zoom=zoomX;
 zoomX=zoomY;
 zoomY=zoom;
}
 

