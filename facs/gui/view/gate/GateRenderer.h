
// // license___here_h


#ifndef GateRenderer__H
#define GateRenderer__H

#include <QList>
#include <QPainter>

class Gate;
class QPainter;
class ViewTransform;
class ViewSettings; 
class GateHandle;

// package facsanadu.gui.view.gate;

// // Renderer of one type of gates

class GateRenderer
{
public:

 virtual void render(Gate* gate, QPainter& p, ViewTransform* w, 
   ViewSettings* viewsettings, QList<GateHandle*> handles) = 0;
};


#endif // __H
 



