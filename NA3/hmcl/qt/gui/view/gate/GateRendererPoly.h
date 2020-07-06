
// // license___here_h


#ifndef GateRendererPoly__H
#define GateRendererPoly__H


// package facsanadu.gui.view.gate;


// // Renderer for polygon gates
class GateRendererPoly : implements GateRenderer
{
public:

  void render(final Gate gate, QPainter p, final ViewTransform w, final ViewSettings viewsettings, Collection<GateHandle> handles);
};

#endif // __H
 



