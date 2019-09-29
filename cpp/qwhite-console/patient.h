
#ifndef PATIENT__H
#define PATIENT__H

#include "accessors.h"

#include <QString>
#include <QtGlobal>
#include <QDate>

class QWhite_Column_Set;

class Patient
{

 quint64 patient_id_;
 QString name_;
 QDate birthdate_;
 QString gender_;

public:

 ACCESSORS(quint64 ,patient_id)
 ACCESSORS(QString ,name)
 ACCESSORS(QDate ,birthdate)
 ACCESSORS(QString ,gender)



 Patient();

 void supply_data(QByteArray& qba, QWhite_Column_Set& columns);
 void absorb_data(const QByteArray& qba, QWhite_Column_Set& columns);




};

#endif
