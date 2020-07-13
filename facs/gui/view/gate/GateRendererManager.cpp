
// // license___here_h


#include "GateRendererManager.h"

#include "GateRendererRect.h"
#include "GateRendererRoot.h"
#include "GateRendererRange.h"
#include "GateRendererPoly.h"
#include "GateRendererEllipse.h"


#include "../gates/gate-info.h"



// package facsanadu.gui.view.gate;


GateRenderer* GateRendererManager::getGateRenderer(Gate* g)
{
 QString cn = g->class_name();

 if(cn == "GateRect")
   return new GateRendererRect();
 else if(cn == "GateRoot")
   return new GateRendererRoot();
 else if(cn == "GateRange")
   return new GateRendererRange();
 else if(cn == "GatePolygon")
   return new GateRendererPoly();
 else if(cn == "GateEllipse")
   return new GateRendererEllipse();
 else
   return nullptr; //throw new RuntimeException("no renderer");
}


