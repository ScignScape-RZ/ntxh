
// // license___here_h


#ifndef GateRenderer__H
#define GateRenderer__H


#include <QPainter>


// package facsanadu.gui.view.gate;

// // Renderer of one type of gates

class GateRenderer
{
public:

 void render(Gate gate, QPainter p, ViewTransform w, ViewSettings viewsettings, Collection<GateHandle> handles) = 0;
};


#endif // __H
 



