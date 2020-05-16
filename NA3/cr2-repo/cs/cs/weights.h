
#ifndef WEIGHTS__H
#define WEIGHTS__H

#include <QtGlobal>
#include <QMap>

typedef quint32 u4;

typedef double r8;


class Weights
{
 QMap<QString, r8> domain_weights_;

 QMap<QString, QMap<u4, r8>> dimension_weights_;


public:

 Weights(QMap<QString, r8>& domain_weights, 
   QMap<QString, QMap<u4, r8>>& dimension_weights);

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


