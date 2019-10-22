
#include <QDebug>

#include "wcm/wcm-database.h"
#include "wcm/wcm-column.h"
#include "wcm/wcm-column-set.h"

//#include "patient.h"

//#include "whitedb.h"

#include <QCoreApplication>

#include "wcm/wcm-hypernode.h"
#include "wcm/wcm-hyponode.h"



int main2(int argc, char *argv[])
{
 WCM_Database wcmd("100", DEFAULT_WCM_FOLDER "/dbs/test-100.wdb");

 wcmd.re_create();

 WCM_Column* patient_type_column = wcmd.create_new_column("@Patient");
 WCM_Column* patient_default_column = wcmd.create_new_column("Default@Patient");

 WCM_Column* name_column = wcmd.create_new_column("Patient::Name");
 WCM_Column* patient_id_column = wcmd.create_new_column("Patient::Id");

 wcmd.save();

 return 0;
}

int main(int argc, char *argv[])
{
 WCM_Database wcmd("100", DEFAULT_WCM_FOLDER "/dbs/test-100.wdb");

 wcmd.load();

 WCM_Hypernode whn;

 QByteArray qba;

 wcmd.retrieve_record(qba, "Default@Patient", "Patient::Id", 1000);

 WCM_Column_Set qwcs(wcmd);

 QMap<quint32, QString> icm;
 icm[2] = "Patient::Id";

 whn.set_indexed_column_map(&icm);
 whn.absorb_data(qba, qwcs);

 whn.with_hyponode(0) << [](WCM_Hyponode& who)
 {
  QVariant qv = who.qt_encoding();
  QString qs = qv.toString();
  qDebug() << qs;
 };

 whn.with_hyponode(1) << [](WCM_Hyponode& who)
 {
  QVariant qv = who.qt_encoding();
  QDate qd = qv.toDate();
  qDebug() << qd.toString();
 };

 whn.with_hyponode(2) << [&wcmd](WCM_Hyponode& who)
 {
  wg_int wgi = who.wgdb_encoding().data;
  quint32 pi = wcmd.wdb().decode_u4(wgi);
  qDebug() << pi;
 };

// quint32 record_index;

// wcmd.add_record("@Patient", "Default@Patient", qba, record_index);

 return 0;

}

int main1(int argc, char *argv[])
{
 WCM_Database wcmd("100", DEFAULT_WCM_FOLDER "/dbs/test-100.wdb");
 qRegisterMetaType<WCM_Encoding_Package>();

 wcmd.load();
 
 WCM_Hypernode whn;

 WCM_Hyponode* who1 = new WCM_Hyponode;
 WCM_Hyponode* who2 = new WCM_Hyponode;
 WCM_Hyponode* who3 = new WCM_Hyponode;

 QVariant v1(QString("Test Name"));
 QVariant v2(QDate::fromString("June 4, 2005", "MMMM d, yyyy"));
 wg_int v3 = wcmd.wdb().encode_u4(1000);
 
 who1->set_qt_encoding(v1);
 who2->set_qt_encoding(v2);
 who3->set_wgdb_encoding({v3});

 whn.add_hyponodes({who1, who2, who3});

 QMap<quint32, QString> icm;
 icm[2] = "Patient::Id";

 whn.set_indexed_column_map(&icm);

 WCM_Column_Set qwcs(wcmd);

 QByteArray qba;

 whn.supply_data(qba, qwcs);

 quint32 record_index;

 wcmd.add_record("@Patient", "Default@Patient", qba, record_index);
 wcmd.save();
 return 0;
}
