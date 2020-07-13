
// // license___here_h


#ifndef ViewSettings__H
#define ViewSettings__H

#include <QVector>


// package facsanadu.gui.view;

// // Johan Henriksson

class Histogram;
class TransformationStack;
class GatingResult;

class Gate;
class Dataset;

// // temp
#include<QList>
#define LinkedList QList


class ViewSettings
{
 //Which gate the view should pick data from
 Gate* gate_;
 
 int indexX_; //=7;
 int indexY_; //=6;
 
 //FCS space * scale = screen space (almost)
 double scaleX_; //=1;
 double scaleY_; //=1;
 
 double zoomX_; //=1; //For speed, this is integrated into the scale whenever needed
 double zoomY_; //=1;

 TransformationStack* transformation_; //=new TransformationStack();

 int numHistBins_; // = 50;
 
public:

 ViewSettings();

 int indexX() const { return indexX_; }  //=7;
 int indexY() const { return indexY_; } 

 void set_indexX(int i) { indexX_ = i; }
 void set_indexY(int i) { indexY_ = i; }
 void set_gate(Gate* g) { gate_ = g; }

 void set_zoomX(double d) { zoomX_ = d; }
 void set_zoomY(double d) { zoomY_ = d; }
 void set_numHistBins(int n) { numHistBins_ = n; } 

 double scaleX() const { return scaleX_; }
 double scaleY() const { return scaleY_; }

 double zoomX() const { return zoomX_; }
 double zoomY() const { return zoomY_; }

 TransformationStack* transformation() { return transformation_; }

 //  // Set the scale to cover the given max and min values
 void autoscale(QVector<double> max, QVector<double> min);

 // // Get the maximum for a channel
 QVector<double> getMaxForChannel(Dataset* dataset);

 // // Get the minimum value for channel
 QVector<double> getMinForChannel(Dataset* dataset);

 // // Get the maximum value for all channels
 QVector<double> getMaxForChannels(QList<Dataset*> datasets); //Collection<Dataset> dataset
 
 // // Get the minimum value for all channels
 QVector<double> getMinForChannels(QList<Dataset*> datasets);

 // // Autoscale several views according to several datasets
 static void autoscale(LinkedList<Dataset*> selds, LinkedList<ViewSettings*> selviews);

 // // Get the name of this view
 QString getName();
// {
//  //Use gate name as name of view
//  return gate_->name();
// }

 Gate* gate()
 {
  //Use gate name as name of view
  return gate_;
 }


 /**
  * Compute histogram from data
  */
 Histogram* computeHistogram(Dataset* data, GatingResult* gr);

 /**
  * Check if the view settings is for a histogram
  */
 bool isHistogram();

 void setHistogram(int chanid);

 bool coversXandY(int indexX2, int indexY2) const;
 bool coversX(int indexX2) const;

 void swapAxis();
 
};

#endif // __H
 



