
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
 quint64 raw_data_;

public:

 ACCESSORS__SDECLARE(wg_enc ,wgdb_encoding)
 ACCESSORS__GET(wg_enc ,wgdb_encoding)

 ACCESSORS__GET(quint64 ,raw_data)
 void set_raw_data(quint64 raw_data, quint32 size);

 ACCESSORS(QVariant ,qt_encoding)

 //quint64 defers_to_wg() const;
 WCM_Encoding_Package::Tuple get_encoding_tuple() const;

 template<typename STREAM_Type>
 friend STREAM_Type& operator <<(STREAM_Type& lhs, const WCM_Hyponode& rhs)
 {
  WCM_Encoding_Package::Tuple tpl = rhs.get_encoding_tuple();
  switch(tpl.kind)
  {
  case 0: lhs << rhs.qt_encoding_; break;
  case 1: lhs << (quint64) rhs.wgdb_encoding_.data; break;
  case 2: lhs << tpl.blob_size; lhs << rhs.raw_data_; break;

  // //  This is by default but it's expected that someone
   //    using tpl.raw option will re-implement this case.
  case 3: lhs << tpl.raw; lhs << (quint64) rhs.wgdb_encoding_.data;
    lhs << rhs.raw_data_; break;

  }
 }

 WCM_Hyponode();
};

#endif
