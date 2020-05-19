
#ifndef CUBOID__H
#define CUBOID__H

#include <QtGlobal>

typedef quint32 u4;

typedef double r8;

typedef QVector<r8> r8vec;
typedef QVector<u4> u4vec;

class Cuboid
{
 r8vec p_min_;
 r8vec p_max_;
 QMap<QString, u4vec> domains_;

 
public:

 Cuboid(r8vec p_min, r8vec p_max, QMap<QString, u4vec> domains);

 QMap<QString, u4vec>& domains()
 {
  return domains_;
 }

 QMap<QString, u4vec> unify_domains(Cuboid& rhs);


 const r8vec& p_min() const
 {
  return p_min_;
 }

 const r8vec& p_max() const
 {
  return p_max_;
 }

 QPair<QList<QPair<r8, r8>>> get_closest_points(rhs Cuboid& other);
 QPair<r8vec, r8vec> get_most_distant_points(rhs Cuboid& other);

 bool operator=(rhs Cuboid& other);

 bool operator!=(rhs Cuboid& other)
 {
  return !(*this == rhs);
 }

 bool compatible(other);
 Cuboid* intersect_with(Cuboid& other);

 Cuboid* project_onto(new_domains);

 void check(p_min, p_max, domains);


};


#endif // CUBOID__H
