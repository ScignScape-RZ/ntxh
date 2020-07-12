
// // license___here_h


#ifndef GateHandle__H
#define GateHandle__H

class MainWindow;

// package facsanadu.gui.view.gate;

//import facsanadu.gui.MainWindow;

/**
 * 
 * 
 * @author Johan Henriksson
 *
 */
class GateHandle
{
public:

 virtual double getX() = 0;
 virtual double getY() = 0;
 virtual void move2(MainWindow* w, double nx, double ny) = 0;
};


#endif // __H
 



