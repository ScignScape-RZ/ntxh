
#ifndef CS__H
#define CS__H

#include <QtGlobal>

typedef quint32 r8;

typedef double r8;

class Conceptual_Space
{
 void check_domain_structure(domains, n_dim);

public:

 Conceptual_Space();

 r8 distance(x, y, weights);

 void add_concept(key);
 void delete_concept(key);
 
 void round(? x);
 bool equal(x, y);
 
 


};


#endif // CORE__H
