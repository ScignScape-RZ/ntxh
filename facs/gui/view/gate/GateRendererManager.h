
// // license___here_h


#ifndef GateRendererManager__H
#define GateRendererManager__H

class Gate;
class GateRenderer;

// package facsanadu.gui.view.gate;

// // Manager of gate renderers

class GateRendererManager
{
public:
	/**
	 * Get a suitable renderer for the gate
	 */
 static GateRenderer* getGateRenderer(Gate* g);
};

#endif // __H
 



