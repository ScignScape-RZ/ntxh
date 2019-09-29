
#include "patient.h"

#include <QDataStream>
#include <QIODevice>

#include "qwhite/qwhite-column-set.h"

Patient::Patient()
{

}

void Patient::supply_data(QByteArray& qba, QWhite_Column_Set& columns)
{
 QDataStream qds(&qba, QIODevice::WriteOnly);

 qds << columns["Patient::Id"](patient_id_);
 qds << columns["Patient::Name"](name_);

// qds << columns.into("Patient::Id").as<std::string>(patient_id_);
 //qds <<
// qds << columns["Patient::Id"](patient_id_);
// //qds << operator[](columns["Patient::Id"]<std::string>(patient_id_);
// qds << columns["Patient::Name"](name_);
// qds << columns["Patient::Birthdate"](birthdate_);
// qds << gender_;
}

void Patient::absorb_data(const QByteArray& qba, QWhite_Column_Set& columns)
{
 QDataStream qds(qba);

 qds >> columns("Patient::Id")(patient_id_); //(patient_id_);
 qds >> columns("Patient::Name")(name_); //(name_);

// qds >> patient_id_;
// qds >> name_;
// qds >> birthdate_;
// qds >> gender_;

}

