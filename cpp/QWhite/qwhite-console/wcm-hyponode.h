
#ifndef WCM_HYPONODE__H
#define WCM_HYPONODE__H

#include "accessors.h"

#include <QString>
#include <QList>
#include <QDate>

#include "_whitedb.h"

#include "qwhite/qwhite-database.h"

class QWhite_Column_Set;
class WCM_Hyponode;
class WCM_Type;


class WCM_Hyponode
{
 wg_enc wgdb_encoding_;
 QVariant qt_encoding_;

public:

 ACCESSORS(wg_enc ,wgdb_encoding)
 ACCESSORS(QVariant ,qt_encoding)

 template<typename STREAM_Type>
 friend STREAM_Type& operator <<(STREAM_Type& lhs, const WCM_Hyponode& rhs)
 {
  lhs << (quint64) rhs.wgdb_encoding_.data;
  lhs << rhs.qt_encoding_;
  return lhs;
 }

 WCM_Hyponode();
};

#endif
