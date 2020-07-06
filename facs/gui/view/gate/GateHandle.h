
// // license___here_h


#ifndef GateHandle__H
#define GateHandle__H

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
 double getX() = 0;
 double getY() = 0;
 void move2(MainWindow w, double nx, double ny) = 0;
};


#endif // __H
 



