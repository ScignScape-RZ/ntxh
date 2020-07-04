//package facsanadu.gui;


FacsanaduProject::FacsanaduProject()
{
 gateset_ = new GateSet();
 datasets_ = new LinkedList<Dataset>();
 views_ = new LinkedList<ViewSettings>();
 profchan_ = new LinkedList<ProfChannel>();

 gatingResult_ = new HashMap<Dataset, GatingResult>();

 compensation_ = new Compensation();
}

GatingResult* FacsanaduProject::getGatingResult(Dataset ds)
{
 return getCreateGatingResult(ds); //Why a separate method here??
}

GatingResult* FacsanaduProject::getCreateGatingResult(Dataset ds)
{
 synchronized (gatingResult)
 {
  if(gatingResult.get(ds)==nullptr) 
  {
   GatingResult gr = new GatingResult(gateset);
   gatingResult.put(ds, gr);
   return gr;
  }
  return gatingResult.get(ds);
 }
}

void FacsanaduProject::performGating(LinkedList<Dataset> listDatasets)
{
 gatingResult.clear();
 for(Dataset ds : listDatasets)
 {
  GatingResult gr=getCreateGatingResult(ds);//new GatingResult();
  gr.perform(gateset, ds);
  gatingResult.put(ds, gr);
 }
}


void FacsanaduProject::addDataset(File path) throws IOException
{
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
  throw new IOException("Cannot recognize file");
}

void FacsanaduProject::updateCompensation()
{
 compensation.updateMatrix(this);
 compensation.apply(this);
}


void FacsanaduProject::addDataset(Dataset ds)
{
 ds.computeProfChannel(this, null);
 datasets.add(ds);
 //recalcProfChan();
 updateCompensation();
 //What about gating?
}

int FacsanaduProject::getNumChannels()
{
 if(datasets.size()==0)
   return 0;
 else
   return datasets.get(0).getChannelInfo().size();
}


ArrayList<ChannelInfo> FacsanaduProject::getChannelInfo()
{
 ArrayList<ChannelInfo>* names = new ArrayList<ChannelInfo>();
 if(!datasets.isEmpty())
 {
  Dataset ds=datasets.get(0);
  names=ds.getChannelInfo();
 }
 return names;
}


void FacsanaduProject::recalcProfChan()
{
 recalcProfChan(nullptr);
}

void FacsanaduProject::recalcProfChan(ProfChannel chChanged)
{
 for(Dataset ds:datasets)
 {
  ds.computeProfChannel(this, chChanged);
 }
}


