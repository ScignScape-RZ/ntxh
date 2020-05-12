
#ifndef CUBOID__H
#define CUBOID__H

#include <QtGlobal>

typedef quint32 r8;

typedef double r8;

class Cuboid
{

public:

 Cuboid(p_min, p_max, domains);

 void get_most_distant_points(rhs Cuboid& other);

 bool operator=(rhs Cuboid& other);

 bool operator!=(rhs Cuboid& other)
 {
  return !(*this == rhs);
 }

 bool compatible(other);
 Cuboid* intersect_with(other);

 Cuboid* project_onto(new_domains);

 void check(p_min, p_max, domains);


};


#endif // CUBOID__H
