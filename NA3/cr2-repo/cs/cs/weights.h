
#ifndef WEIGHTS__H
#define WEIGHTS__H

#include <QtGlobal>

typedef quint32 r8;

typedef double r8;

class Weights
{

public:

 Weights();

 <?> normalize(weights, total);

 bool operator=(const Weights& other);
 bool operator!=(const Weights& other)
 {
  return !(*this == other);
 }

 Weights* merge_with(Weights& other, s = 0.5, t = 0.5);
 Weights* project_onto(new_domains);

 


};


#endif // WEIGHTS__H


