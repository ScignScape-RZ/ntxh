
#ifndef CS__H
#define CS__H

#include <QtGlobal>

#define QtINF qInf()
#define QtNegINF -QtINF



typedef quint32 u4;

typedef QVector<u4> u4vec;

//typedef QMap<QString, u4vec>;

typedef double r8;

class Concept;

class Weights;

class Conceptual_Space
{
 u4 number_of_dimensions_;

 const QMap<QString, u4vec>* domains_;
 QStringList dimension_names_;

 QMap<QString, Concept*> concepts_;
 QMap<QString, QString> concept_colors_;

 Weights* default_weights_;

 void check_domain_structure(domains, number_of_dimensions);

public:

 Conceptual_Space(u4 number_of_dimensions, 
   const QMap<QString, QVector<u4>>& domains, 
   QStringList dimension_names = {});

 r8 distance(Concept& x, Concept& y, Weights& weights);

 void add_concept(QString key, Concept* concept, QString color = {});
 void delete_concept(key);

 void between(Concept& first, Concept& middle, Concept& second,  
Weights* weights = nullptr, QString method="crisp");
 
 void round(? x);
 bool equal(x, y);
 
 


};


#endif // CORE__H
