
// // license___here_h


#ifndef GateRendererRange__H
#define GateRendererRange__H

#include <QPainter>

// package facsanadu.gui.view.gate;

// // Renderer for rectangular gates
class GateRendererRange : // implements GateRenderer
{
public:
 void render(final Gate gate, QPainter p, ViewTransform w, final ViewSettings viewsettings, Collection<GateHandle> handles);

};

#endif // __H
 

