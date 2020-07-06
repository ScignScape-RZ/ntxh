
// // license___here_h


#ifndef GateRendererRoot__H
#define GateRendererRoot__H

#include <QPainter>


// package facsanadu.gui.view.gate;

// // Renderer for root gates

class GateRendererRoot: // implements GateRenderer
{
public: 
 void render(Gate gate, QPainter p, ViewTransform w, ViewSettings viewsettings, Collection<GateHandle> handles);
};

#endif // __H
 



