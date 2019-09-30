
#ifndef WCM_HYPONODE__H
#define WCM_HYPONODE__H

#include "accessors.h"

#include <QString>
#include <QList>
#include <QDate>

#include "_whitedb.h"

class QWhite_Column_Set;
class WCM_Hyponode;
class WCM_Type;


class WCM_Hyponode
{
 wg_int wgdb_encoding_;
 QVariant qt_encoding_;

public:

 ACCESSORS(wg_int ,wgdb_encoding)
 ACCESSORS(QVariant ,qt_encoding)

 WCM_Hyponode();
};

#endif
