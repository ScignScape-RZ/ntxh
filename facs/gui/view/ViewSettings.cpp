
// // license___here

#include "ViewSettings.h"

#include "Histogram.h"

#include "../data/Dataset.h"
#include "../gates/gate-info.h"


#include "../gates/gate-info.h"

#include "../gates/GatingResult.h"

#include <QtGlobal>
#include <QSet>

#include "../transformations/TransformationStack.h"



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

void ViewSettings::autoscale(QVector<double> max, QVector<double> min)
{
 //Currently min values are not used
 Q_UNUSED(min)

 double maxx = max[indexX_];
 double maxy = max[indexY_];
 scaleX_ = 1.0 / (maxx * zoomX_);
 scaleY_ = 1.0 / (maxy * zoomY_);
} 


 /**
  * Get the maximum for a channel
  */
QVector<double> ViewSettings::getMaxForChannel(Dataset* dataset)
{
 QVector<double> val(dataset->getNumChannels());
    // = new QList<double> //?[dataset->getNumChannels()];

 for(int i = 0; i < val.length(); ++i)
 {
  val[i] = -std::numeric_limits<double>::max();
 }

 for(int i = 0; i < dataset->getNumObservations(); ++i)
 {
  for(int j=0; j < val.length(); ++j)
  {
   val[j] = qMax(val[j], dataset->getAsFloatCompensated(i,j) );
  }
 }
 val = transformation_->perform(val);
 return val;
}

 /**
  * Get the minimum value for channel
  */
QVector<double> ViewSettings::getMinForChannel(Dataset* dataset)
{
 QVector<double> vals(dataset->getNumChannels());
   // = new QVector<double>; //[dataset->getNumChannels()];

 for(int i = 0; i < vals.length(); ++i)
   vals[i] = std::numeric_limits<double>::max();

 for(int i = 0; i < dataset->getNumObservations(); ++i)
 {
  for(int j=0;j<vals.length();j++)
  {
   vals[j] = qMin(vals[j], dataset->getAsFloatCompensated(i,j) );
  }
 }
 vals = transformation_->perform(vals); //this is kind of cheating
 return vals;
}

 /**
  * Get the maximum value for all channels
  */
QVector<double> ViewSettings::getMaxForChannels(QList<Dataset*> dataset)
{
 if(dataset.size() == 0)
   return {};
 else
 {
  int numchan = dataset.first()->getNumChannels();
   
  QVector<double> val(numchan);// = new QVector<double>; // [numchan];
  for(int i = 0; i < val.length(); ++i)
  {
   val[i] = -std::numeric_limits<double>::max();
  }
  for(Dataset* ds : dataset)
  {
   QVector<double> cmax = getMaxForChannel(ds);
   for(int j=0; j < numchan; ++j)
   {
    val[j] = qMax(val[j],cmax[j]);
   }
  }
  return val;
 }
}
 
 /**
  * Get the minimum value for all channels
  */
QVector<double> ViewSettings::getMinForChannels(QList<Dataset*> dataset)
{
 if(dataset.isEmpty())
   return {};

 else
 {
  int numchan = dataset.first()->getNumChannels();
   
  QVector<double> val(numchan); // = new QList<double>; //[numchan];
  for(int i=0;i<val.length();i++)
  {
   val[i] = std::numeric_limits<double>::max();
  }
  for(Dataset* ds : dataset)
  {
   QVector<double> cmax = getMinForChannel(ds);
   for(int j = 0; j<numchan; ++j)
   {
    val[j] = qMin(val[j], cmax[j]);
   }
  }
  return val;
 }
}

 /**
  * Autoscale several views according to several datasets
  */
void ViewSettings::autoscale(LinkedList<Dataset*> selds,
  LinkedList<ViewSettings*> selviews)
{
 if(!selds.isEmpty())
 {
  for(ViewSettings* vs : selviews)
  {
   //Might be possible to optimize this if there are many different kind of views
   QVector<double> max = vs->getMaxForChannels(selds);
   QVector<double> min = vs->getMinForChannels(selds);
   vs->autoscale(max,min);
  }
 }
}

 /**
  * Get the name of this view
  */
QString ViewSettings::getName()
{
 //Use gate name as name of view
 return gate_->name();
}


 /**
  * Compute histogram from data
  */
Histogram* ViewSettings::computeHistogram(Dataset* data, GatingResult* gr)
{
 Histogram* h = new Histogram();
 h->setup(0, 1.0/scaleX_, numHistBins_);
 QList<int> accepted = gr->getAcceptedFromGate(gate_);
 if(! accepted.isEmpty() )
 {
  for(int i=0;i<accepted.size();i++)
  {
   int ind=accepted.at(i);
   double x=transformation_->perform(data->getAsFloatCompensated(ind, indexX_ ), indexX_ );
   h->countEvent(x);
  }
 }
 return h;
}


 /**
  * Check if the view settings is for a histogram
  */
bool ViewSettings::isHistogram()
{
 return indexX_ == indexY_;
}


void ViewSettings::setHistogram(int chanid)
{
 indexX_ = indexY_ = chanid;
}



bool ViewSettings::coversXandY(int indexX2, int indexY2) const
{
 QSet<int> ind; //=new HashSet<Integer>(); //? 
 ind.insert(indexX_);
 ind.insert(indexY_);
 return ind.contains(indexX2) && ind.contains(indexY2);
}

bool ViewSettings::coversX(int indexX2) const
{
 QSet<int> ind; //=new HashSet<Integer>(); //? 
 ind.insert(indexX_);
 ind.insert(indexY_);
 return ind.contains(indexX2);
}


void ViewSettings::swapAxis()
{
 int axis = indexX_;
 indexX_ = indexY_;
 indexY_ = axis;
 
 double scale = scaleX_;
 scaleX_ = scaleY_;
 scaleY_ = scale;
  
 double zoom = zoomX_;
 zoomX_ = zoomY_;
 zoomY_ = zoom;
}



