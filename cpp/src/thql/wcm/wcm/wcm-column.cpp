
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "wcm-column.h"

WCM_Column::WCM_Column(QString name, quint32 database_column_code)
 : Flags(0), name_(name), database_column_code_(database_column_code),
   effective_field_number_(0), record_index_field_number_(0), record_count_(0)
{

}

WCM_Column::WCM_Column()
 : WCM_Column(QString(), 0)
{

}

quint32 WCM_Column::get_next_record_index()
{
 if(requires_record_specific_index())
   return ++record_count_;
 return 0;
}


qint8 WCM_Column::get_record_index_field_number()
{
 if(record_index_field_number_ > 0)
 {
  return record_index_field_number_;
 }
 int result = flags.database_automatically_detects_column_code? 0:1;
// if(flags.column_to_record_link)
// {
//  ++result;
// }
// if(flags.record_to_column_link)
// {
//  ++result;
// }
 if(flags.use_varying_record_index_field_number)
 {
  return result;
 }
 record_index_field_number_ = result;
 return result;
}

qint8 WCM_Column::get_effective_field_number()
{
 if(effective_field_number_ > 0)
 {
  return effective_field_number_;
 }
 int result = flags.database_automatically_detects_column_code? 0:1;
 if(!flags.no_column_to_record_link)
 {
  ++result;
 }
 if(flags.record_to_column_link)
 {
  ++result;
 }
 if(flags.use_varying_effective_field_number)
 {
  return result;
 }
 effective_field_number_ = result;
 return result;
}

