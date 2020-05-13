
#ifndef CORE__H
#define CORE__H

#include <QtGlobal>

typedef quint32 u4;

typedef double r8;

typedef QVector<r8> r8vec;
typedef QVector<u4> u4vec;

class Cuboid;


class Core
{
//    """A concept's core, consisting of a set of cuboids with nonempty intersection.
    
//    Implementation of the crisp Simple Star-Shaped Set (SSSS)"""

 QVector<Cuboid*> cuboids_;
 QMap<QString, u4vec> domains_;



public:

 Core(QVector<Cuboid*> cuboids, QMap<QString, u4vec> domains);

 bool operator=(const Core& rhs);
 bool operator!=(const Core& rhs) { return !(*this == rhs); }

 QList<?> find_closest_point_candidates(? point);
 ? unify_with(const Core& other);

 QPair<Core*, Core*> cut_at(dimension, value);
 Core* project_onto(new_domains);
 void midpoint();

 void get_center();
 void check(cuboids, domains):

 Core* from_cuboids(cuboids, domains);
 void simplify(cuboids);

};


#endif // CORE__H