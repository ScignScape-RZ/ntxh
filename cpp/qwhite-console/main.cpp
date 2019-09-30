
#include <QDebug>

#include "qwhite/qwhite-database.h"
#include "qwhite/qwhite-column.h"
#include "qwhite/qwhite-column-set.h"

#include "patient.h"

//#include "whitedb.h"

#include <QNetworkAccessManager>
#include <QEventLoop>
#include <QUrl>
#include <QUrlQuery>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QCoreApplication>

#include "wcm-hypernode.h"
#include "wcm-hyponode.h"



int main(int argc, char *argv[])
{
 QWhite_Database qwdb("100", "/home/nlevisrael/mb/whitedb/QWhite/databases/test/test-100.wdb");

 qwdb.re_create();

 QWhite_Column* patient_type_column = qwdb.create_new_column("@Patient");
 QWhite_Column* patient_default_column = qwdb.create_new_column("Default@Patient");

 QWhite_Column* name_column = qwdb.create_new_column("Patient::Name");
 QWhite_Column* patient_id_column = qwdb.create_new_column("Patient::Id");

 qwdb.save();

 return 0;
}

int main1(int argc, char *argv[])
{
 QWhite_Database qwdb("100", "/home/nlevisrael/mb/whitedb/QWhite/databases/test/test-100.wdb");

 qwdb.load();
 
 WCM_Hypernode whn;

 WCM_Hyponode* who1 = new WCM_Hyponode;
 WCM_Hyponode* who2 = new WCM_Hyponode;
 WCM_Hyponode* who3 = new WCM_Hyponode;

 QVariant v1(QString("Test Name")); 
 QVariant v2(QDate::fromString("June 4, 2005")); 
 wg_int v3 = qwdb.wdb().encode_u4(1000);
 
 whn.add_hyponodes({who1, who2, who3});

 QWhite_Column_Set qwcs(qwdb);

 QByteArray qba;

 whn.supply_data(qba, qwcs);

 quint32 record_index;

 qwdb.add_record("@Patient", "Default@Patient", qba, record_index);
 qwdb.save();
 return 0;
}




int main5(int argc, char *argv[])
{
 QWhite_Database qwdb("100", "/home/nlevisrael/mb/whitedb/QWhite/databases/test/test-100.wdb");

 qwdb.load();
 Patient patient;

 patient.set_name("Test Name");
 patient.set_birthdate(QDate::fromString("June 4, 2005"));
 patient.set_patient_id(1000);
 patient.set_gender("Male");

 QWhite_Column_Set qwcs(qwdb);

 QByteArray qba;

 patient.supply_data(qba, qwcs);

 quint32 record_index;

 qwdb.add_record("@Patient", "Default@Patient", qba, record_index);
 qwdb.save();
 return 0;
}


int main3(int argc, char *argv[])
{
 QWhite_Database qwdb("100", "/home/nlevisrael/mb/whitedb/QWhite/databases/test/test-100.wdb");

 qwdb.reload();

 return 0;
}


int main2(int argc, char *argv[])
{
 QWhite_Database qwdb("100", "/home/nlevisrael/mb/whitedb/QWhite/databases/test/test-100.wdb");

 qwdb.load();

 Patient patient;

 QByteArray qba;

 qwdb.retrieve_record(qba, "Default@Patient", "Patient::Id", 1000);

 QWhite_Column_Set qwcs(qwdb);

 patient.absorb_data(qba, qwcs);


// quint32 record_index;

// qwdb.add_record("@Patient", "Default@Patient", qba, record_index);

 return 0;

}

