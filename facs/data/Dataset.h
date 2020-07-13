
// // license___here_h

#ifndef Dataset__H
#define Dataset__H

// package facsanadu.data;

#include <QList>
#include <QMap>

// // One data block - an FCS file can contain multiple but the standard encourages against

// //  Note: should separate this from FCS parsing!

class ChannelInfo;
class LengthProfile;

class LengthProfileData;
class FacsanaduProject;
class ProfChannel;


class Dataset
{
 int numChannel_; // =0;
 int numPc_; //=0;

 QList<QList<double>> eventsFloat_; //=new ArrayList<double[]>();
 QList<QList<double>> eventsFloatCompensated_; //=new ArrayList<double[]>();
 int numCompensated_; // = 0;

 QList<ChannelInfo*> channelInfo_; // =new ArrayList<ChannelInfo>();
 QFile source_;
 
 QList<LengthProfile*> lengthprofsInfo_; //=new ArrayList<LengthProfile>();
 QList<LengthProfileData*> lengthprofsData_; //=new ArrayList<LengthProfileData>();

 QMap<QString, QString> metaKeyName_; //=new TreeMap<String, String>();


public:
 
 QList<ChannelInfo*> getChannelInfo();
 
 int getNumObservations();

 int getNumChannels();

 int getNumLengthProfiles();

 QString getName();

 QString get_file_source_name();

 double getAsFloatCompensated(int obs, int indexChan);

 QList<double> getAsFloatCompensated(int obs);
 
 // // Compute profile channels. or only one if not null
 void computeProfChannel(FacsanaduProject* proj, ProfChannel* forPc);

 ChannelInfo* getChannelInfoForProf(ProfChannel* pc);

 void setEvents(QList<QList<double>> e);

 // // Resize the events. Used to make space for virtual channels
 void resizeEvents(int newsize);
};

#endif // Dataset__H
