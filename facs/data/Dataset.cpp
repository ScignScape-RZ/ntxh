
// // license___here_h

#include "dataset.h"

Dataset::Dataset()
{
 numChannel_ = 0;
 numPc_ = 0;

 numCompensated_ = 0;
}


public:

QList<ChannelInfo*> Dataset::getChannelInfo()
{
 return channelInfo_;
}


int Dataset::getNumObservations()
{
 return eventsFloat_.size();
}


int Dataset::getNumChannels()
{
 return numCompensated_;
//  return numChannel+numPc;
}


int Dataset::getNumLengthProfiles()
{
 return lengthprofsInfo_.size();
}


QString Dataset::getName()
{
 return source_.fileName();
}


double Dataset::getAsFloatCompensated(int obs, int indexChan)
{
 return eventsFloatCompensated_.get(obs)[indexChan];
  //return eventsFloat.get(obs)[indexChan];
}


QList<double> Dataset::getAsFloatCompensated(int obs)
{
 return eventsFloatCompensated.get(obs);
//  return eventsFloat.get(obs);
}
 

// // Compute profile channels. or only one if not null
void Dataset::computeProfChannel(FacsanaduProject proj, ProfChannel forPc)
{
 /*
  //If deleting or adding a channel... I find it fine enough to recompute everything. But this should
  //not be done if just modifying a gate
  HashSet<ProfChannel> oldPc=new HashSet<ProfChannel>();
  for(ChannelInfo i:channelInfo)
   if(i.pc!=null)
    oldPc.add(i.pc);
  if(!oldPc.equals(new HashSet<ProfChannel>(proj.profchan)))
   {
   //System.out.println("Recomp all chan");
   
   //Recompute all channels
   for(ChannelInfo i:new ArrayList<ChannelInfo>(channelInfo))
    if(i.pc!=null)
     channelInfo.remove(i);
   for(ProfChannel pc:proj.profchan)
    {
    ChannelInfo i=new ChannelInfo();
    i.label=pc.getName();
    i.pc=pc;
    channelInfo.add(i);
    }
   //Add new channels
   numPc=proj.profchan.size();
   resizeEvents(numChannel+numPc);
   for(int i=0;i<numPc;i++)
    {
    int toi=numChannel+i;
    ChannelInfo ci=channelInfo.get(toi);
    for(int j=0;j<getNumObservations();j++)
     {
     double[] d=eventsFloat.get(j);
     d[toi]=ci.pc.calc(lengthprofsData.get(j));
     }
    }
   }
  else if(forPc!=null)
   {
   //Update only one channel
   ChannelInfo ci=getChannelInfoForProf(forPc);
   int toi=channelInfo.indexOf(ci);
   for(int j=0;j<getNumObservations();j++)
    {
    double[] d=eventsFloat.get(j);
    d[toi]=forPc.calc(lengthprofsData.get(j));
    }
   }
  else
   {
   System.out.println("hmmm. prof chan nothing to do");
   }
*/
}

ChannelInfo* Dataset::getChannelInfoForProf(ProfChannel pc)
{
 for(ChannelInfo ci:channelInfo)
 {
  if(ci.pc==pc)
    return ci;
 }
 throw new RuntimeException("No channel info for prof channel");
}

void Dataset::setEvents(QList<QList<double>> e)
{
 eventsFloat=e;
 numChannel=0;
 if(getNumObservations()>0)
   numChannel=eventsFloat.get(0).length;
}

 // // Resize the events. Used to make space for virtual channels
void Dataset::resizeEvents(int newsize)
{
 QList<QList<double>> newEventsFloat; // =new ArrayList<double[]>(eventsFloat.size());
 for(QList<double> o : eventsFloat)
 {
  QList<double> n; // =new double[newsize];
  //?System.arraycopy(o, 0, n, 0, numChannel);
  newEventsFloat.add(n);
 }
 eventsFloat=newEventsFloat;
}


#endif // Dataset__H
