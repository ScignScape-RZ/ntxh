
// // license___here_h


#ifndef GateRendererRoot__H
#define GateRendererRoot__H


#include "GateRenderer.h"


#include <QPainter>

#include <QList>

class Gate;
class ViewTransform;
class ViewSettings;
class GateHandle;

// package facsanadu.gui.view.gate;

// // Renderer for root gates

class GateRendererRoot: public GateRenderer
{
public:

 void render(const Gate* gate, QPainter& p, ViewTransform* w, 
   const ViewSettings* viewsettings, QList<GateHandle*> handles) Q_DECL_OVERRIDE;

};


#endif // __H
 



