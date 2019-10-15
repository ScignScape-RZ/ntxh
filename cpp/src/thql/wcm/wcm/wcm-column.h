
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef WCM_COLUMN__H
#define WCM_COLUMN__H

//#include <whitedb/dbapi.h>
//#include <whitedb/indexapi.h>

extern "C" {
//?#define class _class_
#include "whitedb/_whitedb.h"
//?#undef class
}


#include <QString>

#include <QtGlobal>

#include "accessors.h"
#include "flags.h"


class WCM_Column
{
public:

 flags_(1)
  bool no_column_to_record_link:1;
  bool record_to_column_link:1;
  bool singleton:1;
  bool record_type_external:1;
  bool use_varying_effective_field_number:1;
  bool use_varying_record_index_field_number:1;
  bool supports_column_to_record_alignment:1;
  bool database_automatically_detects_column_code:1;
 _flags

 qint8 effective_field_number_;
 qint8 record_index_field_number_;

 quint32 database_column_code_;

 quint32 record_count_;

 QString name_;

public:

 ACCESSORS(QString ,name)
 ACCESSORS(quint32 ,database_column_code)
 ACCESSORS(qint8 ,effective_field_number)
 ACCESSORS(qint8 ,record_index_field_number)
 ACCESSORS(quint32 ,record_count)


 WCM_Column(QString name, quint32 database_column_code);
 WCM_Column();

 qint8 get_effective_field_number();
 qint8 get_record_index_field_number();
 quint32 get_next_record_index();


 bool requires_record_specific_index()
 {
  return !flags.supports_column_to_record_alignment;
 }
};


#endif

