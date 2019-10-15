
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef WCM_COLUMN_SET__H
#define WCM_COLUMN_SET__H

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

#include "wcm-database.h"

#include <exception>

class WCM_Column;
class WCM_Database;



class WCM_Unrecognized_Column_Exception : std::exception
{

};

class WCM_Column_Set
{
 struct WCM_Column_As_Function_Object
 {
  WCM_Database& wcm_db_;
  WCM_Column* column;

  struct WCM_Column_Data_Package
  {
   quint32 record_id;
   quint32 field_number;
  };

  template<typename STREAM_Type>
  friend STREAM_Type& operator <<(STREAM_Type& lhs, const WCM_Column_Data_Package& rhs)
  {
   //?lhs << rhs.column_id;
   lhs << rhs.record_id;
   return lhs;
  }


  template<typename WHITEDB_DATA_Type, typename APPLICATION_DATA_Type>
  WCM_Column_Data_Package as(APPLICATION_DATA_Type rhs)
  {
   quint32 column_specific_record_index;
   quint32 field_number;
   wcm_db_.add_column_entry<WHITEDB_DATA_Type>(column, rhs, column_specific_record_index, field_number);
   WCM_Column_Data_Package result {column_specific_record_index, field_number};
   return result;
  }

  WCM_Column_Data_Package _as(wg_int rhs)
  {
   quint32 column_specific_record_index;
   quint32 field_number;
   wcm_db_._add_column_entry(column, rhs, column_specific_record_index, field_number);
   WCM_Column_Data_Package result {column_specific_record_index, field_number};
   return result;
  }

  template<typename DATA_Type>
  WCM_Column_Data_Package operator ()(DATA_Type rhs);
//  {
//   return as<DATA_Type>(rhs);

//   //wcm_db_.add_column_entry(column, rhs);
//  }


//  template<>
//  WCM_Column_Data_Package operator ()(long rhs);
//  {
//   return _as(rhs);
//  }

//  template<typename DATA_Type>
//  WCM_Column_Data_Package operator ()(ptrdiff_t rhs)
//  {
//   return _as(rhs);
//  }

//  template<typename DATA_Type>
//  WCM_Column_Data_Package operator ()(wg_int rhs)
//  {
//   return _as(rhs);
//  }


  template<typename STREAM_Type, typename DATA_Type>
  friend STREAM_Type operator <<(STREAM_Type lhs, WCM_Column_Data_Package rhs)
  {
   //lhs << rhs.column_id;
   lhs << rhs.record_id;
   return lhs;
  }

 };

 struct WCM_Column_Data_Holder;

 template<typename T>
 struct WCM_Column_Data_Holder_As_Function_Object
 {
  WCM_Column_Data_Holder& dh;
  T& data;
 };

 struct WCM_Column_Data_Holder
 {
  WCM_Database& wcm_db_;
  WCM_Column* column;
  quint32 record_id;

  template<typename T>
  WCM_Column_Data_Holder_As_Function_Object<T> operator()(T& t)
  {
   return {*this, t};
  }
 };

//?
// template<typename STREAM_Type>
// friend const STREAM_Type& operator >>(const STREAM_Type& lhs, WCM_Column_Data_Holder rhs)
// {
//  //?lhs << rhs.column_id;
//  lhs >> rhs.record_id;
//  return lhs;
// }

 template<typename STREAM_Type, typename DATA_Type>
 friend STREAM_Type& operator >>(STREAM_Type& lhs, WCM_Column_Data_Holder_As_Function_Object<DATA_Type> rhs)
 {
  //?lhs << rhs.column_id;
  lhs >> rhs.dh.record_id;
  rhs.dh.wcm_db_.retrieve_value(rhs.dh.column, rhs.dh.record_id, rhs.data);
  return lhs;
 }

 WCM_Database& wcm_db_;
 QMap<QString, WCM_Column*> column_by_name_;

public:

 WCM_Column_Set(WCM_Database& wcm_db);


// template<typename WHITEDB_DATA_Type>
// WCM_Column_As_Function_Object test(QString column_name);
// <std::string>

 WCM_Column_As_Function_Object operator[](QString column_name);

 WCM_Column_Data_Holder operator()(QString column_name);

 template<typename... T>
 void use_columns(T&&... ts)
 {
  use_columns({std::forward<T>(ts)...});
 }

 void use_columns(QStringList column_names);

 void use_columns(std::initializer_list<QString>(strings))
 {
  use_columns(QStringList(strings));
 }


// WCM_Column_As_Function_Object operator[](std::string cn);

};


#endif

