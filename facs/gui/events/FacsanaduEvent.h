
// // license___here_h


#ifndef FacsanaduEvent__H
#define FacsanaduEvent__H

// package facsanadu.gui.events;

// // Any GUI event
class FacsanaduEvent
{
public:

 enum class Description 
 {
  N_A,
  EventCompensationChanged,
  EventDatasetsChanged, 
  EventGatesChanged,
  EventGatesMoved, 
  EventViewsChanged,
 };

 virtual Description get_description()
 {
  return Description::N_A;
 } 
};

class EventCompensationChanged : public FacsanaduEvent // implements ...
{
 Description get_description() Q_DECL_OVERRIDE
 {
  return Description::EventCompensationChanged;
 } 

};

class EventDatasetsChanged : public FacsanaduEvent
{
 Description get_description() Q_DECL_OVERRIDE
 {
  return Description::EventDatasetsChanged;
 } 
};

class EventGatesChanged : public FacsanaduEvent
{
public:

 EventGatesChanged() {}

 Description get_description() Q_DECL_OVERRIDE
 {
  return Description::EventGatesChanged;
 } 
};

class EventGatesMoved : public FacsanaduEvent
{
 Description get_description() Q_DECL_OVERRIDE
 {
  return Description::EventGatesMoved;
 } 
};

class EventViewsChanged : public FacsanaduEvent
{
public:

 EventViewsChanged() {}

 Description get_description() Q_DECL_OVERRIDE
 {
  return Description::EventViewsChanged;
 } 
};


#endif // __H
 

