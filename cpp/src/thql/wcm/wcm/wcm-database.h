
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef WCM_DATABASE__H
#define WCM_DATABASE__H

#include <QVector>

//#include <whitedb/dbapi.h>
//#include <whitedb/indexapi.h>

extern "C" {
//?#define class _class_
#include "whitedb/_whitedb.h"
//?#undef class
}


#include <QString>
#include <QtGlobal>
#include <QMap>
#include <QDate>

#include "accessors.h"

#include "wcm-column.h"

#include "global-types.h"

#include "withs.h"


#include <QVariant>


//#define with_brake std::function<void(z8)> _brake

//#define brake(__VARAGS__) _brake({__VARAGS__})

class WCM_Column;
class WCM_Hyponode;

struct wg_enc
{
 wg_int data;
};

struct WCM_Encoding_Package
{
 quint64 code;

 static WCM_Encoding_Package from_raw_size(u4 blob_size)
 {
  return { (blob_size << 2) + 2 };
 }

 static WCM_Encoding_Package from_raw_data(quint64 d)
 {
  return { d | 2 };
 }

 struct Tuple
 {
  u4 blob_size;
  quint8 kind;
  quint64 raw;
 };

 static Tuple null_tuple()
 {
  return {0, 0, 0};
 }

 Tuple as_tuple() const
 {
  quint64 mask = code & 3;
  switch(mask)
  {
  case 0: return {0, 0, 0};
  case 1: return {0, 1, 0};
  case 2: return { (u4) (code >> 2), 2, 0};
  case 3: return { 0, 3, code - 3};
  }
 }
};

Q_DECLARE_METATYPE(WCM_Encoding_Package)

struct WCM_WhiteDB
{
 void* white_db;

 wg_int encode_u4(u4 x)
 {
  return wg_encode_int(white_db, x);
 }

 u4 decode_u4(wg_int x)
 {
  return wg_decode_int(white_db, x);
 }

 wg_int encode_string(QString str)
 {
  return wg_encode_str(white_db, (char*) str.toStdString().c_str(), NULL);
 }

 QString decode_string(wg_int x)
 {
  std::string ss = wg_decode_str(white_db, x);
  return QString::fromStdString(ss);
 }


};

class WCM_Database
{
 QString name_;
 QString full_path_;

 u4 max_column_code_;

 void* white_db_;
 void* max_column_code_record_;

 QVector<WCM_Column*> columns_;
 QMap<QString, WCM_Column*> columns_map_;

 int column_change_count_;

 QMap<u1, QDateTime> datetimes_;

 wg_int _add_column_entry_(WCM_Column* qc, wg_int data,
   u4& column_specific_record_index, u4& field_number);

 struct For_All_Records_Package
 {
  WCM_Database* _this;
  QString archive_name;
  QString index_column_name;
  wg_int query_param;
  struct FN_Types
  {
   enum class Enum { QBA_Ptr, QBA_Ptr_Brake,
     QBA_Ref, QBA_Ref_Brake,
     QBA_Ref_Count, QBA_Ref_Count_Brake};
   Enum which;
   union fns_union {
    std::function<void(QByteArray*, void*)> fn_QBA_Ptr;
    std::function<void(QByteArray*, void*, brake)> fn_QBA_Ptr_Brake;
    std::function<void(QByteArray&, void*)> fn_QBA_Ref;
    std::function<void(QByteArray&, void*, brake)> fn_QBA_Ref_Brake;
    std::function<void(QByteArray&, void*, u4)> fn_QBA_Ref_Count;
    std::function<void(QByteArray&, void*, u4, brake)> fn_QBA_Ref_Count_Brake;
    ~fns_union()
    {
    }
   };
   fns_union the_fns;
   ~FN_Types()
   {
    switch (which)
    {
#define TEMP_MACRO(arg) \
    case Enum::arg: \
      the_fns.fn_##arg.~function(); \
      break;  \

    TEMP_MACRO(QBA_Ptr)
    TEMP_MACRO(QBA_Ptr_Brake)
    TEMP_MACRO(QBA_Ref)
    TEMP_MACRO(QBA_Ref_Brake)
    TEMP_MACRO(QBA_Ref_Count)
    TEMP_MACRO(QBA_Ref_Count_Brake)

#undef TEMP_MACRO
    }
   }
  };

  void operator <<
    (std::function<void(QByteArray*, void*)> fn);

  void operator <<
    (std::function<void(QByteArray*, void*, brake)> fn);

  void operator <<
    (std::function<void(QByteArray&, void*)> fn);

  void operator <<
    (std::function<void(QByteArray&, void*, brake)> fn);

  void operator <<
    (std::function<void(QByteArray&, void*, u4)> fn);

  void operator <<
    (std::function<void(QByteArray&, void*, u4, brake)> fn);

  void proceed_fns(FN_Types* fns);
 };

 struct New_Hyponode_Array_Package
 {
  WCM_Database* _this;
  u4 size;
  operator WCM_Hyponode**();
  WCM_Hyponode** operator <<
    (std::function<void(WCM_WhiteDB&, WCM_Hyponode*, u4)> fn);
//  WCM_Hyponode** operator <<
//    (std::function<void(WCM_Hyponode*, u4)> fn);
 };

 struct With_New_Hyponode_Array_Package
 {
  WCM_Database* _this;
  u4 size;
  void operator <<
    (std::function<void(WCM_WhiteDB&, WCM_Hyponode**)> fn);
  void operator <<
    (std::function<void(WCM_Hyponode**)> fn);
  void operator <<
    (std::function<void(WCM_Database&, WCM_Hyponode**)> fn);
 };

 struct With_All_Column_Records_Package
 {
  WCM_Database* _this;
  QString col;
  void operator <<
    (std::function<void(QByteArray&)> fn);
  void operator <<
    (std::function<void(QByteArray&, u4)> fn);
 };

 struct With_Check_Create_Package
 {
  WCM_Database* _this;
  void operator <<
    (std::function<void()> fn);

  void operator <<
    (std::function<void(WCM_Database&)> fn);

 };


public:

 ACCESSORS(QString ,name)
 ACCESSORS(QString ,full_path)
 ACCESSORS__RGET(MACRO_PASTE(QMap<u1, QDateTime>) ,datetimes)
 ACCESSORS__SDECLARE(QDateTime ,creation_datetime)

 enum DateTime_Codes {
   Recent_Create = 1, Recent_Load_From_File = 2,
   Created = 3, Last_Load_From_File = 4, Recent_Attach = 5
  };

 QVariantMap datetimes_qvariantmap();
 void init_datetimes(QVariantMap& qvm);
 void reinit_datetimes(QVariantMap& qvm);
 void reinit_datetimes(QVariant qvar);


 WCM_Database(QString name, QString full_path);

 With_All_Column_Records_Package with_all_column_records(QString col)
 {
  return {this, col};
 }

 With_Check_Create_Package with_check_create()
 {
  return {this};
 }

 WCM_Column* get_column_by_name(QString name);

 void set_creation_datetime();
 u4 get_record_count(QString col);

 u4 new_column_code();
 void confirm_new_column_code(u4 id);

 void write_column_data(QByteArray& qba);
 void check_update_column_data();

 QString check_data(QString which);

 QString report_columns(QString separator = "\n");

 QString report_columns_html();

 void* add_record(QString type_column, QString archive_column,
  const QByteArray& qba, u4& record_index);

 // wcmd.retrieve_record(qba, "Default@Patient", "Patient::Id", 1000);

 void* retrieve_record_from_encoding(QByteArray& qba, QString archive_name,
   QString index_column_name, wg_int data);

 void retrieve_all_records_from_encoding(QString archive_name,
   QString index_column_name, wg_int data, QVector<QPair<QByteArray*, void*>>& results);

 void retrieve_record(QByteArray& qba, WCM_Column* qc,
   QString archive_name, wg_query_arg* arglist, u2 asize, void*& result);

 void retrieve_all_records(WCM_Column* qc,
   QString archive_name, wg_query_arg* arglist, u2 asize,
   QVector<QPair<QByteArray*, void*>>* results,
   For_All_Records_Package::FN_Types* fns);

 void retrieve_from_index_record(QByteArray& qba,
   WCM_Column* qc, QString archive_name, void* index_record, void*& result);


 void retrieve_all_records(QByteArray& qba, QString archive_name,
   QString index_column_name, wg_int data, QVector<void*>& results); //, void* prior

 void* retrieve_record(QByteArray& qba, QString archive_name);
 void* retrieve_indexed_record(QByteArray& qba, QString archive_name,
   u4 index);


 template<typename T>
 void* retrieve_record(QByteArray& qba, QString archive_name,
   QString index_column_name, T data)
 {
  wg_int query_param = translate_data_to_query_param(data);
  return retrieve_record_from_encoding(qba, archive_name, index_column_name, query_param);
 }

 template<typename T>
 void retrieve_all_records(QString archive_name,
   QString index_column_name, T data, QVector<QPair<QByteArray*, void*>>& results)
 {
  wg_int query_param = translate_data_to_query_param(data);
  retrieve_all_records_from_encoding(archive_name, index_column_name, query_param, results);
 }

 void construct_query_cursor(WCM_Column*& wcmc, QString index_column_name,
   wg_int query_param, quint64& result);

 template<typename T>
 QPair<quint64, quint64>  construct_query_cursor(QString index_column_name,
   T data)
 {
  wg_int query_param = translate_data_to_query_param(data);
  quint64 result;
  WCM_Column* wcmc;
  construct_query_cursor(wcmc, index_column_name, query_param, result);
  return {(quint64) wcmc, result};
 }

 template<typename T>
 For_All_Records_Package for_all_records(QString archive_name, QString index_column_name,
   T data)
 {
  wg_int query_param = translate_data_to_query_param(data);
  return {this, archive_name, index_column_name, query_param};
 }

 void retrieve_next_record(
   QString archive_name, WCM_Column* wcmc, wg_query* qry,
   QPair<QByteArray*, void*&> result);

 void* retrieve_column_entry_value(WCM_Column* qc, u4 record_id, wg_int& result_value);

 template<typename DATA_Type>
 void untranslate_data(wg_int data, DATA_Type& dt);

 template<typename DATA_Type>
 void retrieve_value(WCM_Column* qc, u4 record_id, DATA_Type& dt)
 {
  wg_int value;
  retrieve_column_entry_value(qc, record_id, value);
  untranslate_data(value, dt);
 }

 WCM_WhiteDB wdb()
 {
  return {white_db_};
 }

 void retrieve();
 void save();
 void create();

 void check_create();

 void re_create();

 void reload();
 void load();

 void reload_from_file();

 void check_delete();
 void init_columns();
 //void init_columns(QByteArray& qba);

 New_Hyponode_Array_Package new_hyponode_array(u4 size)
 {
  return {this, size};
 }

 With_New_Hyponode_Array_Package with_new_hyponode_array(u4 size)
 {
  return {this, size};
 }

 WCM_Column* create_new_column(QString name, void(*fn)(WCM_Column&) = nullptr);

 WCM_Column* create_new_singleton_column(QString name);


 void* create_column_entry_record(WCM_Column* qc,
   u4& record_specific_index, int field_count = 3); //, wg_int column_id)

 void* create_singleton_column_entry_record(WCM_Column* qc,
   int field_count);

 template<typename DATA_Type>
 wg_int translate_data(DATA_Type dt);


 template<typename DATA_Type>
 wg_int translate_data_to_query_param(DATA_Type dt);

 wg_int _add_column_entry(WCM_Column* qc, wg_int data,
   u4& column_specific_record_index, u4& field_number);


 template<typename DATA_Type>
 wg_int add_column_entry(WCM_Column* qc, DATA_Type data,
   u4& column_specific_record_index, u4& field_number)
 {
  wg_int data_as_wg_int = translate_data(data);
  return _add_column_entry_(qc, data_as_wg_int, column_specific_record_index, field_number);

  //  wg_int result = wg_set_field(white_db_, cer, field_number,  data_as_wg_int);
  //  return result;

//  wg_int record_specific_index;
//  void* cer = create_column_entry_record(qc, record_specific_index);
//  if(record_specific_index > 0) //qc->requires_record_specific_index())
//  {
//   qint8 fn = qc->get_record_index_field_number();
////?   wg_set_int_field(white_db_, cer, (int) fn, record_specific_index);
//   column_specific_record_index = record_specific_index;
//   ++column_change_count_;
//  }
//  else
//  {
//   column_specific_record_index = 0;
//  }
//  wg_int data_as_wg_int = translate_data(data);
//  field_number = qc->get_effective_field_number();
//  wg_int result = wg_set_field(white_db_, cer, field_number,  data_as_wg_int);
//  return result;
 }

};

//QString operator "" _q(const char* arr, size_t size)
//{
// std::string ss(arr, size);
// return QString::fromStdString(ss);
//}

struct WCM_String_Literal_Package
{
 const char* cs;
 size_t size;

 QString operator()()
 {
  std::string ss(cs, size);
  return QString::fromStdString(ss);
 }

 wg_int operator[](WCM_Database& w)
 {
  return w.wdb().encode_string(this->operator()());
 }

 wg_int operator[](WCM_WhiteDB& w)
 {
  return w.encode_string(this->operator()());
 }
};

static inline WCM_String_Literal_Package operator ""_q_(const char* arr, size_t size)
{
 return {arr, size};
}


//template<typename DATA_Type>
//wg_int WCM_Database::add_column_entry(WCM_Column* qc, DATA_Type data,
//  u4& column_specific_record_index, u4& field_number)
//{
// wg_int record_specific_index;
// void* cer = create_column_entry_record(qc, record_specific_index);
// if(record_specific_index > 0) //qc->requires_record_specific_index())
// {
//  wg_set_field(white_db_, cer, qc->get_record_index_field_number(), record_specific_index);
//  column_specific_record_index = record_specific_index;
//  ++column_change_count_;
// }
// else
// {
//  column_specific_record_index = 0;
// }
// wg_int data_as_wg_int = translate_data(data);
// field_number = qc->get_effective_field_number();
// wg_int result = wg_set_field(white_db_, cer, field_number, data_as_wg_int);
// return result;
//}


#endif
