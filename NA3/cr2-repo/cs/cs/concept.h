
#ifndef CONCEPT__H
#define CONCEPT__H

#include <QtGlobal>

typedef quint32 r8;

typedef double r8;

class Core;
class Weights;

class Point;
class Conceptual_Space;

class Concept
{
 Conceptual_Space* cs_;
 Core* core_;
 r8 mu_;
 r8 c_;
 Weights* weights_;

 r8 membership_of(Point p);
 void intersection_mu_special_case(QVector<u4>& a, r8 c2, QVector<u4>& b, r8 mu):
 void intersect_fuzzy_cuboids(Cuboid c1, Cuboid c2, Concept& other):

 void check_crisp_betweenness(points, first, second);

public:

 Concept(Conceptual_Space* cs, r8 self, r8 core, r8 mu, r8 c, r8 weights);

 bool operator=(const Concept& rhs);
 bool operator!=(const Concept& rhs) { return !(*this == rhs); }
 
 Concept* intersect_with(const Concept& other);
 Concept* unify_with(const Concept& other);
 Concept* project_onto(? domains);

 QPair<Concept*, Concept*> cut_at(? dimension, ? value);
 QVector<?> reduce_domains(domains, dimensions);

 r8 hypervolume_cuboid(cuboid);
 r8 size();
 bool crisp_subset_of(Concept& other);
 r8 implies(Concept& other);
 r8 similarity_to(Concept& other, QString method="Jaccard");
 r8 between(Concept& first, Concept& second,
    QString method="integral", u4 num_alpha_cuts = 20):

 ? sample(u4 num_samples);

};


#endif 
