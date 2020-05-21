
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

 static QMap<QString, r8> normalize(
   const QMap<QString, r8>&  weights, r8 total);

 bool operator=(const Weights& other);
 bool operator!=(const Weights& other)
 {
  return !(*this == other);
 }

 Weights* merge_with(Weights& other, r8 s = 0.5, r8 t = 0.5);
 Weights* project_onto(const QMap<QString, QString<u4, r8>>& new_domains);

 


};


#endif // WEIGHTS__H


