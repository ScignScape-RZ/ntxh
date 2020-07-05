// package facsanadu.gui.view;

// // Johan Henriksson
class ViewSettings
{
 //Which gate the view should pick data from
 Gate gate;
 
 int indexX_; //=7;
 int indexY_; //=6;
 
 //FCS space * scale = screen space (almost)
 double scaleX_; //=1;
 double scaleY_; //=1;
 
 double zoomX_; //=1; //For speed, this is integrated into the scale whenever needed
 double zoomY_; //=1;

 TransformationStack* transformation_; //=new TransformationStack();

 int numHistBins = 50;
 
 /**
  * Set the scale to cover the given max and min values
  */
 void autoscale(double[] max, double[] min);

 /**
  * Get the maximum for a channel
  */
 QList<double> getMaxForChannel(Dataset dataset);

 /**
  * Get the minimum value for channel
  */
 QList<double> getMinForChannel(Dataset dataset);

 /**
  * Get the maximum value for all channels
  */
 QList<double> getMaxForChannels(Collection<Dataset> dataset);
 
 /**
  * Get the minimum value for all channels
  */
 QList<double> getMinForChannels(Collection<Dataset> dataset);

 /**
  * Autoscale several views according to several datasets
  */
 static void autoscale(LinkedList<Dataset> selds, LinkedList<ViewSettings> selviews);

 /**
  * Get the name of this view
  */
 QString getName()
 {
  //Use gate name as name of view
  return gate.name;
 }


 /**
  * Compute histogram from data
  */
 Histogram computeHistogram(Dataset data, GatingResult gr);

 /**
  * Check if the view settings is for a histogram
  */
 boolean isHistogram();

 void setHistogram(int chanid);

 boolean coversXandY(int indexX2, int indexY2);
 boolean coversX(int indexX2);

 void swapAxis();
 
};


