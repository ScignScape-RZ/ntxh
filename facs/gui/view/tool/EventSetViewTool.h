
// // license___here_h


#ifndef EventSetViewTool__H
#define EventSetViewTool__H


// package facsanadu.gui.view.tool;

//import facsanadu.gui.events.FacsanaduEvent;

/**
 * 
 * 
 * @author Johan Henriksson
 *
 */
class EventSetViewTool : FacsanaduEvent
{
public:

 ViewToolChoice* choice_;
 EventSetViewTool(ViewToolChoice choice);

};

#endif // __H
 



