
// // license___here

#include "FacsanaduProject.h"

#include "../data/Dataset.h"


#include <QMutexLocker>

//package facsanadu.gui;


FacsanaduProject::FacsanaduProject()
{
// gateset_ = new GateSet();
// datasets_ = new LinkedList<Dataset*>();
// views_ = new LinkedList<ViewSettings>();
// profchan_ = new LinkedList<ProfChannel>();

// gatingResult_ = new HashMap<Dataset, GatingResult>();

 compensation_ = nullptr; // hold off ... new Compensation();
}

GatingResult* FacsanaduProject::getGatingResult(Dataset* ds)
{
 return getCreateGatingResult(ds); //Why a separate method here??
}

GatingResult* FacsanaduProject::getCreateGatingResult(Dataset* ds)
{
//? synchronized (gatingResult)
// {
 QMutexLocker lock(&gatingResult_mutex_);

 GatingResult* gr = gatingResult_.value(ds);

 if(gr == nullptr) 
 {
    // gr = new GatingResult(gateset);
  gatingResult_.insert(ds, gr);
 }

 return gr; // gatingResult->get(ds);
 //}
}

void FacsanaduProject::performGating(LinkedList<Dataset*> listDatasets)
{
 gatingResult_.clear();
 for(Dataset* ds : listDatasets)
 {
  GatingResult* gr = getCreateGatingResult(ds);//new GatingResult();
   // gr->perform(gateset, ds);
  gatingResult_.insert(ds, gr);
 }
}


void FacsanaduProject::addDataset(QFile& path) // throws IOException
{
 Q_UNUSED(path)
 /*
 if(FCSFile::isFCSfile(path))
 {
  //Assume it is an FCS file
  addDataset(FCSFile::load(path));
 }
 else if(CopasIO.isCopasFile(path))
 {
  //Assume COPAS file
  addDataset(CopasIO::readAll(path));
 }
 else
   ;// throw Facs_IOException("Cannot recognize file");
 */
}

void FacsanaduProject::updateCompensation()
{
 //? compensation_->updateMatrix(this);
 //? compensation_->apply(this);
}


void FacsanaduProject::addDataset(Dataset* ds)
{
  //? ds->computeProfChannel(this, nullptr);
 
 datasets_.append(ds);
 //recalcProfChan();
 updateCompensation();
 //What about gating?
}

int FacsanaduProject::getNumChannels()
{
 if(datasets_.isEmpty())
   return 0;
 else
   return datasets_.first()->getChannelInfo().size();
}


QList<ChannelInfo*> FacsanaduProject::getChannelInfo()
{
 QList<ChannelInfo*> names; // = new ArrayList<ChannelInfo>();
 if(!datasets_.isEmpty())
 {
  Dataset* ds = datasets_.first();
  names = ds->getChannelInfo();
 }
 return names;
}


void FacsanaduProject::recalcProfChan()
{
 recalcProfChan(nullptr);
}

void FacsanaduProject::recalcProfChan(ProfChannel* chChanged)
{
 for(Dataset* ds : datasets_)
 {
  ds->computeProfChannel(this, chChanged);
 }
}


