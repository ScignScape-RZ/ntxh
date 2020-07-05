// package facsanadu.gui.view.gate;


GateRenderer GateRendererManager::getGateRenderer(Gate g)
{
 if(g instanceof GateRect)
   return new GateRendererRect();
 else if(g instanceof GateRoot)
   return new GateRendererRoot();
 else if(g instanceof GateRange)
   return new GateRendererRange();
 else if(g instanceof GatePolygon)
   return new GateRendererPoly();
 else if(g instanceof GateEllipse)
   return new GateRendererEllipse();
 else
   throw new RuntimeException("no renderer");
 }
}
