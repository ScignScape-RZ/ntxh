
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


#include <QVariant>

class WCM_Column;
class WCM_Hyponode;

struct wg_enc
{
 wg_int data;
};

struct WCM_Encoding_Package
{
 quint64 code;

 static WCM_Encoding_Package from_raw_size(quint32 blob_size)
 {
  return { (blob_size << 2) + 2 };
 }

 static WCM_Encoding_Package from_raw_data(quint64 d)
 {
  return { d | 2 };
 }

 struct Tuple
 {
  quint32 blob_size;
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
  case 2: return { (quint32) (code >> 2), 2, 0};
  case 3: return { 0, 3, code - 3};
  }
 }
};

Q_DECLARE_METATYPE(WCM_Encoding_Package)

struct WCM_WhiteDB
{
 void* white_db;

 wg_int encode_u4(quint32 x)
 {
  return wg_encode_int(white_db, x);
 }

 quint32 decode_u4(wg_int x)
 {
  return wg_decode_int(white_db, x);
 }

 wg_int encode_string(QString str)
 {
  return wg_encode_str(white_db, (char*) str.toStdString().c_str(), NULL);
 }


};

class WCM_Database
{
 QString name_;
 QString full_path_;

 quint32 max_column_code_;

 void* white_db_;
 void* max_column_code_record_;

 QVector<WCM_Column*> columns_;
 QMap<QString, WCM_Column*> columns_map_;

 int column_change_count_;

 wg_int _add_column_entry_(WCM_Column* qc, wg_int data,
   quint32& column_specific_record_index, quint32& field_number);

 struct New_Hyponode_Array_Package
 {
  WCM_Database* _this;
  quint32 size;
  WCM_Hyponode** operator <<
    (std::function<void(WCM_WhiteDB&, WCM_Hyponode*, quint32)> fn);
 };

public:

 ACCESSORS(QString ,name)
 ACCESSORS(QString ,full_path)

 WCM_Database(QString name, QString full_path);

 WCM_Column* get_column_by_name(QString name);

 quint32 new_column_code();
 void confirm_new_column_code(quint32 id);

 void write_column_data(QByteArray& qba);
 void check_update_column_data();

 QString check_data(QString which);

 QString report_columns(QString separator = "\n");

 QString report_columns_html();

 void* add_record(QString type_column, QString archive_column,
  const QByteArray& qba, quint32& record_index);

 // qwdb.retrieve_record(qba, "Default@Patient", "Patient::Id", 1000);

 void* retrieve_record(QByteArray& qba, QString archive_name,
   QString index_column_name, wg_int data);

 template<typename T>
 void* retrieve_record(QByteArray& qba, QString archive_name,
   QString index_column_name, T data)
 {
  wg_int query_param = translate_data_to_query_param(data);
  return retrieve_record(qba, archive_name, index_column_name, query_param);
 }

 void* retrieve_column_entry_value(WCM_Column* qc, quint32 record_id, wg_int& result_value);

 template<typename DATA_Type>
 void untranslate_data(wg_int data, DATA_Type& dt);

 template<typename DATA_Type>
 void retrieve_value(WCM_Column* qc, quint32 record_id, DATA_Type& dt)
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

 New_Hyponode_Array_Package new_hyponode_array(quint32 size)
 {
  return {this, size};
 }


 WCM_Column* create_new_column(QString name);

 void* create_column_entry_record(WCM_Column* qc,
   wg_int& record_specific_index, int field_count = 3); //, wg_int column_id)

 template<typename DATA_Type>
 wg_int translate_data(DATA_Type dt);


 template<typename DATA_Type>
 wg_int translate_data_to_query_param(DATA_Type dt);

 wg_int _add_column_entry(WCM_Column* qc, wg_int data,
   quint32& column_specific_record_index, quint32& field_number);


 template<typename DATA_Type>
 wg_int add_column_entry(WCM_Column* qc, DATA_Type data,
   quint32& column_specific_record_index, quint32& field_number)
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

//template<typename DATA_Type>
//wg_int WCM_Database::add_column_entry(WCM_Column* qc, DATA_Type data,
//  quint32& column_specific_record_index, quint32& field_number)
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
