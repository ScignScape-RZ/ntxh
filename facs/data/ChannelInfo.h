
// // license___here_h

#ifndef ChannelInfo__H
#define ChannelInfo__H

// // package facsanadu.data;

class ProfChannel;

// // Information about one channel
class ChannelInfo
{
 QString label_;
 QString name_;

 ProfChannel* pc_; //=nullptr;

public:

 ChannelInfo(QString label, QString name);
 
 QString formatName();

 QString getShortestName();
 
};

#endif // ChannelInfo__H


