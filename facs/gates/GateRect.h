
// // license___here_h


#ifndef GateRect__H
#define GateRect__H

#include "gate-info.h"

#include <QtGlobal>

// package facsanadu.gates;

/**
 * 
 * Rectangular gate
 * 
 * @author Johan Henriksson
 *
 */
class GateRect : Gate
{
public:

 int indexX, indexY;

 double x1, x2, y1, y2;

 double ix1, ix2, iy1, iy2;

 void updateInternal()
 {
  ix1 = qMin(x1, x2);
  iy1 = qMin(y1, y2);
  
  ix2 = qMax(x1, x2);
  iy2 = qMax(y1, y2);
  setUpdated();
 }
 
 bool classify(QList<double> obs)
 {
  return
    obs[indexX]>=ix1 && obs[indexX]<=ix2 &&
    obs[indexY]>=iy1 && obs[indexY]<=iy2;
 }

};

#endif // __H

