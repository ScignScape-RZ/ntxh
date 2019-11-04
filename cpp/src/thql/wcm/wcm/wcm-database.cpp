
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "wcm-database.h"
#include "wcm-column.h"

#include "wcm-hyponode.h"

#include "global-types.h"

#include <QByteArray>

#include <QDataStream>
#include <QtGlobal>

#include <QFileInfo>

#include <QDebug>

//#include "/ext_root/whitedb/whitedb-0.7.3/Db/dbindex.h"
//#include "/ext_root/whitedb/whitedb-0.7.3/Db/dbindex.c"

WCM_Database::WCM_Database(QString name, QString full_path)
 : name_(name), full_path_(full_path), max_column_code_(0),
   white_db_(nullptr), max_column_code_record_(nullptr), column_change_count_(0)
{
}

WCM_Database::New_Hyponode_Array_Package::operator WCM_Hyponode**()
{
 WCM_Hyponode** result = new WCM_Hyponode* [size];
 for(u4 i = 0; i < size; ++i)
 {
  result[i] = new WCM_Hyponode;
 }
 return result;
}

void WCM_Database::With_New_Hyponode_Array_Package::operator <<
  (std::function<void(WCM_WhiteDB&, WCM_Hyponode**)> fn)
{
 WCM_Hyponode** result = new WCM_Hyponode* [size];
 for(u4 i = 0; i < size; ++i)
 {
  result[i] = new WCM_Hyponode;
 }
 WCM_WhiteDB wdb = _this->wdb();
 fn(wdb, result);
 for(u4 i = 0; i < size; ++i)
 {
  delete result[i];
 }
 delete [] result;
}

void WCM_Database::With_New_Hyponode_Array_Package::operator <<
  (std::function<void(WCM_Database&, WCM_Hyponode**)> fn)
{
 WCM_Hyponode** result = new WCM_Hyponode* [size];
 for(u4 i = 0; i < size; ++i)
 {
  result[i] = new WCM_Hyponode;
 }
 fn(*_this, result);
 for(u4 i = 0; i < size; ++i)
 {
  delete result[i];
 }
 delete [] result;
}

void WCM_Database::With_New_Hyponode_Array_Package::operator <<
  (std::function<void(WCM_Hyponode**)> fn)
{
 WCM_Hyponode** result = new WCM_Hyponode* [size];
 for(u4 i = 0; i < size; ++i)
 {
  result[i] = new WCM_Hyponode;
 }
 fn(result);
 for(u4 i = 0; i < size; ++i)
 {
  delete result[i];
 }
 delete [] result;
}

WCM_Hyponode** WCM_Database::New_Hyponode_Array_Package::operator <<
  (std::function<void(WCM_WhiteDB&, WCM_Hyponode*, u4)> fn)
{
 WCM_Hyponode** result = new WCM_Hyponode* [size];
 for(u4 i = 0; i < size; ++i)
 {
  result[i] = new WCM_Hyponode;
  WCM_WhiteDB wdb = _this->wdb();
  fn(wdb, result[i], i);
 }
 return result;
}


//template<>
QDataStream& operator <<(QDataStream& lhs, const WCM_Column* const rhs)
{
 quint8 rF = rhs->Flags;
 lhs << rF;
 lhs << rhs->name();
 lhs << rhs->database_column_code();
 lhs << rhs->record_count();
 lhs << rhs->effective_field_number();
 lhs << rhs->record_index_field_number();
 return lhs;
}

QDataStream& operator >>(QDataStream& lhs, WCM_Column* const rhs)
{
 quint8 f;
 lhs >> f;
 rhs->Flags = f;
 QString n;
 lhs >> n;
 rhs->set_name(n);
 u4 code;
 lhs >> code;
 rhs->set_database_column_code(code);
 u4 record_count;
 lhs >> record_count;
 rhs->set_record_count(record_count);

 qint8 efn;
 lhs >> efn;
 rhs->set_effective_field_number(efn);

 qint8 rifn;
 lhs >> rifn;
 rhs->set_record_index_field_number(rifn);
 return lhs;
}

QDataStream& operator >>(QDataStream& lhs, QVector<WCM_Column*>& rhs)
{
 u4 len;
 lhs >> len;
 rhs.fill(nullptr, len);
 for(WCM_Column*& qc : rhs)
 {
  qc = new WCM_Column;
  lhs >> qc;
 }
 return lhs;
}

//template<>
//QDataStream& operator<<(QDataStream& s, const QVector<T>& v)
//{
//    s << u4(v.size());
//    for (typename QVector<T>::const_iterator it = v.begin(); it != v.end(); ++it)
//        s << *it;
//    return s;
//}

WCM_Column* WCM_Database::get_column_by_name(QString name)
{
 return columns_map_.value(name, nullptr);
}

QString WCM_Database::check_data(QString which)
{
#define TEMP_MACRO(key, field) \
 { #key, \
  (QString(WCM_Database::*)())(&WCM_Database::field) \
 }, \

 static QMap<QString, QString(WCM_Database::*)()> static_map
 {
  TEMP_MACRO(name ,name)
  TEMP_MACRO(full-path ,full_path)
  TEMP_MACRO(report-columns ,report_columns)
  TEMP_MACRO(report-columns-html ,report_columns_html)
 };

#undef TEMP_MACRO

 QString result;

 if(static_map.contains(which))
 {
  auto fn = static_map[which];
  result = (this->*fn)();
 }
 return result;
}


void WCM_Database::create()
{
 char* np = const_cast<char*>(name_.toStdString().c_str());
 white_db_ = wg_attach_database(np, 0);
 //white_db_ = wg_attach_database(name_.toStdString().c_str(), 0);
 max_column_code_record_ = wg_create_record(white_db_, 2);
 wg_set_field(white_db_, max_column_code_record_, 0, wg_encode_int(white_db_, 0));

 QByteArray qba;
 write_column_data(qba);
 wg_set_field(white_db_, max_column_code_record_, 1, wg_encode_blob(white_db_, qba.data(), NULL, qba.size()));

}

QString WCM_Database::report_columns_html()
{
 QString result = report_columns("<br/>");
 return result;
}

QString WCM_Database::report_columns(QString separator)
{
 QString result;
 //  columns_ -> scan do .(c result-set) [columns_] ->
 //  columns_ -> span do .(c) [result] ->
 //    result += c ->
 //

 for(WCM_Column* c : columns_)
 {
  result += c->name() + separator;
 }
 return result;
}


u4 WCM_Database::new_column_code()
{
 return max_column_code_ + 1;
}

void WCM_Database::confirm_new_column_code(u4 id)
{
 max_column_code_ = id;
 wg_set_field(white_db_, max_column_code_record_, 0, wg_encode_int(white_db_, max_column_code_ + 1));
}

//void WCM_Database::init_columns(QByteArray& qba)
//{
// QDataStream qds(&qba, QIODevice::ReadOnly);
// u4 len;
// qds >> len;
// qds >> columns_;
//}

void WCM_Database::init_columns()
{
 max_column_code_record_ = wg_get_first_record(white_db_);
 wg_int wgi = wg_get_field(white_db_, max_column_code_record_, 0);
 max_column_code_ = wg_decode_int(white_db_, wgi) - 1;
 wg_int wgi1 = wg_get_field(white_db_, max_column_code_record_, 1);

 char* blob = wg_decode_blob(white_db_, wgi1);
 wg_int wlen = wg_decode_blob_len(white_db_, wgi1);

 QByteArray qba(blob, wlen);
 QDataStream qds(&qba, QIODevice::ReadOnly);
 qds >> columns_;
 for(WCM_Column* qc : columns_)
 {
  columns_map_[qc->name()] = qc;
 }
}


void WCM_Database::load()
{
 char* np = const_cast<char*>(name_.toStdString().c_str());
 white_db_ = wg_attach_database(np, 0);
 init_columns();
// max_column_code_record_ = wg_get_first_record(white_db_);
// wg_int wgi = wg_get_field(white_db_, max_column_code_record_, 0);
// max_column_code_ = wg_decode_int(white_db_, wgi);
}

void WCM_Database::reload()
{
 char* np = const_cast<char*>(name_.toStdString().c_str());
 white_db_ = wg_attach_database(np, 0);
 reload_from_file();

// char* fp = const_cast<char*>(full_path_.toStdString().c_str());
// wg_import_dump(white_db_, fp);
// init_columns();

// max_column_code_record_ = wg_get_first_record(white_db_);
// wg_int wgi = wg_get_field(white_db_, max_column_code_record_, 0);
// max_column_code_ = wg_decode_int(white_db_, wgi);
}

void WCM_Database::reload_from_file()
{
 char* fp = const_cast<char*>(full_path_.toStdString().c_str());
 wg_import_dump(white_db_, fp);
 init_columns();
}

void WCM_Database::reinit_datetimes(QVariant qvar)
{
 QVariantMap qvm = qvar.toMap();
 reinit_datetimes(qvm);
}

void WCM_Database::reinit_datetimes(QVariantMap& qvm)
{
 init_datetimes(qvm);
 if(datetimes_.contains(Recent_Create))
   datetimes_[Created] = datetimes_.take(Recent_Create);
 if(datetimes_.contains(Recent_Load_From_File))
   datetimes_[Last_Load_From_File] = datetimes_.take(Recent_Load_From_File);
 }


void WCM_Database::init_datetimes(QVariantMap& qvm)
{
 QVariantMap result;
 std::map<QString, QVariant> sm = qvm.toStdMap();
 std::map<u1, QDateTime> rsm;
 std::transform(sm.begin(), sm.end(),
   std::inserter(rsm, rsm.end()),
   []( std::pair<QString, QVariant> kv) -> std::pair<u1, QDateTime>
 {
  return {kv.first.toInt(), kv.second.toDateTime()};
 });
 datetimes_ = QMap<u1, QDateTime>(rsm);
}

QVariantMap WCM_Database::datetimes_qvariantmap()
{
 QVariantMap result;
 std::map<u1, QDateTime> sm = datetimes_.toStdMap();
 std::map<QString, QVariant> rsm;
 std::transform(sm.begin(), sm.end(),
   std::inserter(rsm, rsm.end()),
   []( std::pair<u1, QDateTime> kv) -> std::pair<QString, QVariant>
 {
  return {QString::number(kv.first), kv.second};
 });
 return QVariantMap(rsm);
}

void WCM_Database::set_creation_datetime()
{
 datetimes_.insert(Created, QDateTime::currentDateTime());
}

void WCM_Database::set_creation_datetime(QDateTime dtm)
{
 datetimes_.insert(Created, dtm);
}

void WCM_Database::With_Check_Create_Package::operator<<(std::function<void()> fn)
{
 _this->check_create();
 if(_this->datetimes().contains(DateTime_Codes::Recent_Create))
   fn();
};

void WCM_Database::With_Check_Create_Package::operator<<(std::function<void(WCM_Database&)> fn)
{
 _this->check_create();
 if(_this->datetimes().contains(DateTime_Codes::Recent_Create))
   fn(*_this);
};

void WCM_Database::check_create()
{
 char* np = const_cast<char*>(name_.toStdString().c_str());
 white_db_ = wg_attach_existing_database(np);

 if(white_db_)
 {
  init_columns();
  datetimes_[Recent_Attach] = QDateTime::currentDateTime();
 }
 else
 {
  QFileInfo qfi(full_path_);
  if(qfi.exists())
  {
   // //  Here wg_attach_database actually creates the db in shared memory,
    //    take everything else from the file
   white_db_ = wg_attach_database(np, 0);
   reload_from_file();
   datetimes_[Recent_Load_From_File] = QDateTime::currentDateTime();
  }
  else
  {
   // //  Start from scratch as a last resort.
   create();
   datetimes_[Recent_Create] = QDateTime::currentDateTime();
  }
 }
}

void WCM_Database::check_delete()
{
 char* np = const_cast<char*>(name_.toStdString().c_str());
 wg_delete_database(np);
}

void WCM_Database::re_create()
{
 check_delete();
 create();
 save();
}


void WCM_Database::write_column_data(QByteArray& qba)
{
 QDataStream qds(&qba, QIODevice::WriteOnly);
 qds << columns_;
 // qds << columns_.length();
 // for(WCM_Column* qc : columns_)
 // {
 //  qds << qc;
 // }
 //qds << columns_;
}

void* WCM_Database::retrieve_column_entry_value(WCM_Column* qc, u4 record_id, wg_int& result_value)
{
 wg_query_arg arglist [2]; // holds the arguments to the query

 int column_code = qc->database_column_code();
 arglist[0].column = 0;
 arglist[0].cond = WG_COND_EQUAL;
 arglist[0].value = wg_encode_query_param_int(white_db_, column_code);

 int col = qc->get_record_index_field_number();
 arglist[1].column = col;
 arglist[1].cond = WG_COND_EQUAL;
 arglist[1].value = wg_encode_query_param_int(white_db_, record_id);

 wg_query* qry = wg_make_query(white_db_, NULL, 0, arglist, 2);

 void* result = wg_fetch(white_db_, qry);

 if(result)
 {
  int fn = qc->get_effective_field_number();
  result_value = wg_get_field(white_db_, result, fn);
 }
 return result;
}

void* WCM_Database::retrieve_record(QByteArray& qba, QString archive_name)
{
 wg_query_arg result_arglist; // holds the arguments to the query

 WCM_Column* aqc = get_column_by_name(archive_name);

 if(aqc)
 {
  int acolumn_code = aqc->database_column_code();
  result_arglist.column = 0;
  result_arglist.cond = WG_COND_EQUAL;
  result_arglist.value = wg_encode_query_param_int(white_db_, acolumn_code);
  wg_query* aqry = wg_make_query(white_db_, NULL, 0, &result_arglist, 1);
  void* result = wg_fetch(white_db_, aqry);
  if(result)
  {
   int afn = aqc->get_effective_field_number();
   wg_int awgi = wg_get_field(white_db_, result, afn);

   char* blob = wg_decode_blob(white_db_, awgi);
   wg_int wlen = wg_decode_blob_len(white_db_, awgi);
   qba = QByteArray(blob, wlen);
   return result;
  }
 }
 return nullptr;
}

void WCM_Database::With_All_Column_Records_Package::operator<<
  (std::function<void(QByteArray&)> fn)
{
// wcmd.retrieve_indexed_record(qba, "Default@Species", i);
 WCM_Column* aqc = _this->get_column_by_name(col);
 if(!aqc)
   return;
 u4 rc = aqc->record_count();
 for(u4 i = 1; i <= rc; ++i)
 {
  QByteArray qba;
  _this->retrieve_indexed_record(qba, col, i);
  fn(qba);
 }
}

void WCM_Database::With_All_Column_Records_Package::operator<<
  (std::function<void(QByteArray&, u4)> fn)
{
// wcmd.retrieve_indexed_record(qba, "Default@Species", i);
 WCM_Column* aqc = _this->get_column_by_name(col);
 if(!aqc)
   return;
 u4 rc = aqc->record_count();
 for(u4 i = 0; i < rc; ++i)
 {
  QByteArray qba;
  _this->retrieve_indexed_record(qba, col, i + 1);
  fn(qba, i);
 }
}

u4 WCM_Database::get_record_count(QString col)
{
 WCM_Column* aqc = get_column_by_name(col);
 if(!aqc)
   return 0;
 return aqc->record_count();
}

void* WCM_Database::retrieve_indexed_record(QByteArray& qba, QString archive_name,
  u4 index)
{
 wg_query_arg arglist [2]; // holds the arguments to the query
 WCM_Column* aqc = get_column_by_name(archive_name);

 if(aqc)
 {
  int acolumn_code = aqc->database_column_code();
  arglist[0].column = 0;
  arglist[0].cond = WG_COND_EQUAL;
  arglist[0].value = wg_encode_query_param_int(white_db_, acolumn_code);

  int col = aqc->get_record_index_field_number();
  arglist[1].column = col;
  arglist[1].cond = WG_COND_EQUAL;
  arglist[1].value = wg_encode_query_param_int(white_db_, index);

  wg_query* aqry = wg_make_query(white_db_, NULL, 0, arglist, 2);
  void* result = wg_fetch(white_db_, aqry);
  if(result)
  {
   int afn = aqc->get_effective_field_number();
   wg_int awgi = wg_get_field(white_db_, result, afn);

   char* blob = wg_decode_blob(white_db_, awgi);
   wg_int wlen = wg_decode_blob_len(white_db_, awgi);
   qba = QByteArray(blob, wlen);
   return result;
  }
 }
 return nullptr;
}

void WCM_Database::retrieve_all_records(QByteArray& qba, QString archive_name,
  QString index_column_name, wg_int query_param, QVector<void*>& results)
{
}

void WCM_Database::retrieve_from_index_record(QByteArray& qba,
  WCM_Column* qc, QString archive_name, void* index_record, void*& result)
{
 //int col = qc->get_effective_field_number();
 int fn = qc->get_record_index_field_number();
   //int fn = qc->get_effective_field_number();
 wg_int wgi = wg_get_field(white_db_, index_record, fn);

 wg_int index = wg_decode_int(white_db_, wgi);
 wg_query_arg result_arglist [2]; // holds the arguments to the query

 WCM_Column* aqc = get_column_by_name(archive_name);

 int acolumn_code = aqc->database_column_code();
 result_arglist[0].column = 0;
 result_arglist[0].cond = WG_COND_EQUAL;
 result_arglist[0].value = wg_encode_query_param_int(white_db_, acolumn_code);

 int acol = qc->get_record_index_field_number();
 result_arglist[1].column = acol;
 result_arglist[1].cond = WG_COND_EQUAL;
 result_arglist[1].value = wg_encode_query_param_int(white_db_, index);

 wg_query* aqry = wg_make_query(white_db_, NULL, 0, result_arglist, 2);

 result = wg_fetch(white_db_, aqry);

 if(result)
 {
  int afn = aqc->get_effective_field_number();
  wg_int awgi = wg_get_field(white_db_, result, afn);

  char* blob = wg_decode_blob(white_db_, awgi);
  wg_int wlen = wg_decode_blob_len(white_db_, awgi);

  qba = QByteArray(blob, wlen);
 }

 wg_free_query_param(white_db_, result_arglist[0].value);
 wg_free_query_param(white_db_, result_arglist[1].value);
 wg_free_query(white_db_, aqry);

}

void WCM_Database::construct_query_cursor(WCM_Column*& wcmc,
  QString index_column_name,
  wg_int query_param, quint64& result)
{
 wcmc = get_column_by_name(index_column_name);
 if(wcmc)
 {
//  wcmc = qc;
  wg_query_arg arglist [2]; // holds the arguments to the query

  int column_code = wcmc->database_column_code();
  arglist[0].column = 0;
  arglist[0].cond = WG_COND_EQUAL;
  arglist[0].value = wg_encode_query_param_int(white_db_, column_code);

  int col = wcmc->get_effective_field_number();
  arglist[1].column = col;
  arglist[1].cond = WG_COND_EQUAL;
  arglist[1].value = query_param;

//   wg_free_query_param(_this->white_db_, arglist[0].value);
//   wg_free_query_param(_this->white_db_, arglist[1].value);
//  }
  wg_query* qry = wg_make_query(white_db_, NULL, 0, arglist, 2);

  result = (quint64) qry;
 }
}

void WCM_Database::retrieve_next_record(
  QString archive_name, WCM_Column* wcmc, wg_query* qry,
  QPair<QByteArray*, void*&> result)
{
 void* index_record = wg_fetch(white_db_, qry);
 if(!index_record)
   return;
// WCM_Column* qc = get_column_by_name(index_column_name);
 retrieve_from_index_record(*result.first, wcmc, archive_name, index_record, result.second);
}


void WCM_Database::retrieve_all_records(WCM_Column* qc,
  QString archive_name, wg_query_arg* arglist, u2 asize,
  QVector<QPair<QByteArray*, void*>>* results,
  For_All_Records_Package::FN_Types* fns)
{
 wg_query* qry = wg_make_query(white_db_, NULL, 0, arglist, asize);
 u4 count = 0;
 for(;;)
 {
  void* index_record = wg_fetch(white_db_, qry);
  if(!index_record)
    break;
  void* result;
  QByteArray* qba = new QByteArray;
  retrieve_from_index_record(*qba, qc, archive_name, index_record, result);
  if(results)
    results->push_back({qba, result});
  if(fns)
  {
   switch (fns->which)
   {
   case WCM_Database::For_All_Records_Package::FN_Types::Enum::QBA_Ptr:
    fns->the_fns.fn_QBA_Ptr(qba, result);
    break;
   case WCM_Database::For_All_Records_Package::FN_Types::Enum::QBA_Ref:
    fns->the_fns.fn_QBA_Ref(*qba, result);
    delete qba;
    break;
   case WCM_Database::For_All_Records_Package::FN_Types::Enum::QBA_Ref_Brake:
    {
     brake test_brk = brake(nullptr);
     auto brk = brake::make_break_function(test_brk);
     fns->the_fns.fn_QBA_Ref_Brake(*qba, result, {brk});
     delete qba;
     if(test_brk.fn)
       goto End_Loop;
    }
    break;
   case WCM_Database::For_All_Records_Package::FN_Types::Enum::QBA_Ref_Count:
    fns->the_fns.fn_QBA_Ref_Count(*qba, result, count);
    delete qba;
    ++count;
    break;
   case WCM_Database::For_All_Records_Package::FN_Types::Enum::QBA_Ref_Count_Brake:
    {
     brake test_brk = brake(nullptr);
     auto brk = brake::make_break_function(test_brk);
     fns->the_fns.fn_QBA_Ref_Count_Brake(*qba, result, count, {brk});
     delete qba;
     if(test_brk.fn)
       goto End_Loop;
     ++count;
    }
    break;
   }
  }
 }
End_Loop:
 wg_free_query(white_db_, qry);
}


void WCM_Database::retrieve_record(QByteArray& qba,
  WCM_Column* qc, QString archive_name, wg_query_arg* arglist, u2 asize, void*& result)
{
 wg_query* qry = wg_make_query(white_db_, NULL, 0, arglist, asize);
 void* index_record = wg_fetch(white_db_, qry);
 if(index_record)
 {
  retrieve_from_index_record(qba, qc, archive_name, index_record, result);
 }
 wg_free_query(white_db_, qry);
}

void WCM_Database::For_All_Records_Package::proceed_fns(FN_Types* fns)
{
 WCM_Column* qc = _this->get_column_by_name(index_column_name);
 if(qc)
 {
  wg_query_arg arglist [2]; // holds the arguments to the query

  int column_code = qc->database_column_code();
  arglist[0].column = 0;
  arglist[0].cond = WG_COND_EQUAL;
  arglist[0].value = wg_encode_query_param_int(_this->white_db_, column_code);

  int col = qc->get_effective_field_number();
  arglist[1].column = col;
  arglist[1].cond = WG_COND_EQUAL;
  arglist[1].value = query_param;

  _this->retrieve_all_records(qc, archive_name, arglist, 2, nullptr, fns);
  wg_free_query_param(_this->white_db_, arglist[0].value);
  wg_free_query_param(_this->white_db_, arglist[1].value);
 }
}

void WCM_Database::For_All_Records_Package::operator<<
  (std::function<void (QByteArray*, void*)> fn)
{
 WCM_Database::For_All_Records_Package::FN_Types fnt
  {FN_Types::Enum::QBA_Ptr, {.fn_QBA_Ptr = {fn} }};
 proceed_fns(&fnt);
}

void WCM_Database::For_All_Records_Package::operator<<
  (std::function<void (QByteArray*, void*, brake)> fn)
{
 WCM_Database::For_All_Records_Package::FN_Types fnt
  {FN_Types::Enum::QBA_Ptr_Brake, {.fn_QBA_Ptr_Brake = {fn} }};
 proceed_fns(&fnt);
}

void WCM_Database::For_All_Records_Package::operator<<
  (std::function<void (QByteArray&, void*)> fn)
{
 WCM_Database::For_All_Records_Package::FN_Types fnt
  {FN_Types::Enum::QBA_Ref, {.fn_QBA_Ref = {fn} }};
 proceed_fns(&fnt);
}

void WCM_Database::For_All_Records_Package::operator<<
  (std::function<void(QByteArray&, void*, brake)> fn)
{
 WCM_Database::For_All_Records_Package::FN_Types fnt
  {FN_Types::Enum::QBA_Ref_Brake, {.fn_QBA_Ref_Brake = {fn} }};
 proceed_fns(&fnt);
}

void WCM_Database::For_All_Records_Package::operator<<
  (std::function<void (QByteArray&, void*, u4)> fn)
{
 WCM_Database::For_All_Records_Package::FN_Types fnt
  {FN_Types::Enum::QBA_Ref_Count, {.fn_QBA_Ref_Count = {fn} }};
 proceed_fns(&fnt);
}

void WCM_Database::For_All_Records_Package::operator<<
  (std::function<void(QByteArray&, void*, u4, brake)> fn)
{
 WCM_Database::For_All_Records_Package::FN_Types fnt
  {FN_Types::Enum::QBA_Ref_Count_Brake, {.fn_QBA_Ref_Count_Brake = {fn} }};
 proceed_fns(&fnt);
}

void WCM_Database::retrieve_all_records_from_encoding(QString archive_name,
  QString index_column_name, wg_int query_param, QVector<QPair<QByteArray*, void*>>& results)
{
 WCM_Column* qc = get_column_by_name(index_column_name);
 if(qc)
 {
  wg_query_arg arglist [2]; // holds the arguments to the query

  int column_code = qc->database_column_code();
  arglist[0].column = 0;
  arglist[0].cond = WG_COND_EQUAL;
  arglist[0].value = wg_encode_query_param_int(white_db_, column_code);

  int col = qc->get_effective_field_number();
  arglist[1].column = col;
  arglist[1].cond = WG_COND_EQUAL;
  arglist[1].value = query_param;

  retrieve_all_records(qc, archive_name, arglist, 2, &results, nullptr);
  wg_free_query_param(white_db_, arglist[0].value);
  wg_free_query_param(white_db_, arglist[1].value);
 }
}



void* WCM_Database::retrieve_record_from_encoding(QByteArray& qba, QString archive_name,
  QString index_column_name, wg_int query_param)
{
 WCM_Column* qc = get_column_by_name(index_column_name);
 void* result;
 if(qc)
 {
  wg_query_arg arglist [2]; // holds the arguments to the query

  int column_code = qc->database_column_code();
  arglist[0].column = 0;
  arglist[0].cond = WG_COND_EQUAL;
  arglist[0].value = wg_encode_query_param_int(white_db_, column_code);

  int col = qc->get_effective_field_number();
  arglist[1].column = col;
  arglist[1].cond = WG_COND_EQUAL;
  arglist[1].value = query_param;

  retrieve_record(qba, qc, archive_name, arglist, 2, result);
  wg_free_query_param(white_db_, arglist[0].value);
  wg_free_query_param(white_db_, arglist[1].value);
 }
 else
 {
  result = nullptr;
 }
 return result;
}

//  wg_query* qry = wg_make_query(white_db_, NULL, 0, arglist, 2);

//  void* index_record = wg_fetch(white_db_, qry);
//  if(index_record)
//  {
//   //int col = qc->get_effective_field_number();
//   int fn = qc->get_record_index_field_number();
//   //int fn = qc->get_effective_field_number();
//   wg_int wgi = wg_get_field(white_db_, index_record, fn);

//   wg_int index = wg_decode_int(white_db_, wgi);
//   wg_query_arg result_arglist [2]; // holds the arguments to the query

//   WCM_Column* aqc = get_column_by_name(archive_name);

//   int acolumn_code = aqc->database_column_code();
//   result_arglist[0].column = 0;
//   result_arglist[0].cond = WG_COND_EQUAL;
//   result_arglist[0].value = wg_encode_query_param_int(white_db_, acolumn_code);

//   int acol = qc->get_record_index_field_number();
//   result_arglist[1].column = acol;
//   result_arglist[1].cond = WG_COND_EQUAL;
//   result_arglist[1].value = wg_encode_query_param_int(white_db_, index);

//   wg_query* aqry = (white_db_, NULL, 0, result_arglist, 2);

//   result = wg_fetch(white_db_, aqry);

//   if(result)
//   {
//    int afn = aqc->get_effective_field_number();
//    wg_int awgi = wg_get_field(white_db_, result, afn);

//    char* blob = wg_decode_blob(white_db_, awgi);
//    wg_int wlen = wg_decode_blob_len(white_db_, awgi);

//    qba = QByteArray(blob, wlen);
//   }
//  }
//  wg_free_query(white_db_, qry);

void* WCM_Database::create_singleton_column_entry_record(WCM_Column* qc,
  int field_count) //, wg_int column_id)
{
 void* result = wg_create_record(white_db_, field_count);
 wg_set_field(white_db_, result, 0, wg_encode_int(white_db_, qc->database_column_code()));
 return result;
}


void* WCM_Database::create_column_entry_record(WCM_Column* qc,
  u4& record_specific_index, int field_count) //, wg_int column_id)
{
 void* result = wg_create_record(white_db_, field_count);
 wg_set_field(white_db_, result, 0, wg_encode_int(white_db_, qc->database_column_code()));
 record_specific_index = qc->get_next_record_index();
 return result;
}

void* WCM_Database::add_record(QString type_column, QString archive_column,
  const QByteArray& qba, u4& record_index)
{
 WCM_Column* aqc = get_column_by_name(archive_column);
// QByteArray qba1(qba.size(), 0);

// int i = 0;
// for(char c : qba)
// {
//  qba1[i] = c;
//  ++i;
// }


 //(qba);

 char* c = const_cast<char*>(qba.data());
 int s = qba.size();
 u4 ri = 0;
 void* result;
 if(aqc->flags.singleton)
   result = create_singleton_column_entry_record(aqc, 2);
 else
   result = create_column_entry_record(aqc, ri, 3);
 record_index = ri;

 if(!aqc->flags.singleton)
 {
  int index_col = aqc->get_record_index_field_number();
  wg_set_field(white_db_, result, index_col,
    wg_encode_int(white_db_, ri));
 }

 int fn = aqc->get_effective_field_number();

 wg_set_field(white_db_, result, fn,
   wg_encode_blob(white_db_, c, NULL, s ));

 return result;
}

void WCM_Database::save()
{
 check_update_column_data();
// void* db = wg_attach_database("100", 0);

//// void* rec = wg_create_record(db, 10);
// void* rec1 = wg_create_record(db, 3);

//// wg_int enc = wg_encode_int(db, 443);
// wg_int enc1 = wg_encode_str(db, "this is my string", NULL);

//// wg_set_field(db, rec, 7, enc);
// int index = 1;
// int column_code = 1;

// wg_set_field(db, rec1, 0, wg_encode_int(db, column_code));
// wg_set_field(db, rec1, 1, wg_encode_int(db, index));

// wg_set_field(db, rec1, 2, enc1);

// QString str = "ok ...";

// QByteArray qba;

// QDataStream qds(&qba, QIODevice::WriteOnly);

// qds << str;

// qds << index;

// quintptr rec = wg_encode_record(db, rec1);
// qds << rec;

// ++index;

// void* rec2 = wg_create_record(db, 3);
// wg_int enc2 = wg_encode_blob(db, qba.data(), NULL, qba.size());

// //wg_int enc = wg_encode_int(db, 443);

// wg_set_field(db, rec2, 0, wg_encode_int(db, index) );

// wg_set_field(db, rec2, 1, enc2);

// wg_set_field(db, rec2, 2, wg_encode_record(db, rec1) );

// wg_create_index(db, 0, WG_INDEX_TYPE_TTREE, NULL, 0);
// wg_create_index(db, 1, WG_INDEX_TYPE_TTREE, NULL, 0);

// wg_int wgi = wg_get_field(db, rec3, 0);
// char* blob = wg_decode_blob(db, wgi);

// wg_int len = wg_decode_blob_len(db, wgi);

// QByteArray qba2(blob, len);
// QDataStream qds1(&qba2, QIODevice::ReadOnly);

// QString s1;

// qds1 >> s1;
// qDebug() << "STR: " << s1;

 std::string fps = full_path_.toStdString();

// char* fp = const_cast<char*>(full_path_.toStdString().c_str());

 char* fp = (char*)(fps.c_str());
 wg_dump(white_db_, fp);

// wg_dump(white_db_, "/home/nlevisrael/mb/whitedb/WCM/databases/test/t-100.wdb");

 //?wg_detach_database(db);
// wg_delete_database("100");

}

void WCM_Database::check_update_column_data()
{
 if(column_change_count_ > 0)
 {
  QByteArray qba;
  write_column_data(qba);
  wg_set_field(white_db_, max_column_code_record_, 1, wg_encode_blob(white_db_, qba.data(), NULL, qba.size()));
  column_change_count_ = 0;
 }
}

WCM_Column* WCM_Database::create_new_singleton_column(QString name)
{
 return create_new_column(name, [](WCM_Column& col)
 {
  col.set_effective_field_number(1);
  col.flags.singleton = true;
 });
}

WCM_Column* WCM_Database::create_new_column(QString name, void(*fn)(WCM_Column&))
{
 u4 id = new_column_code();
 WCM_Column* result = new WCM_Column(name, id);
 if(result)
 {
  if(fn)
  {
   fn(*result);
  }
  columns_.push_back(result);
  columns_map_[name] = result;
  QByteArray qba;
  write_column_data(qba);
  confirm_new_column_code(id);
  wg_set_field(white_db_, max_column_code_record_, 1, wg_encode_blob(white_db_, qba.data(), NULL, qba.size()));
 }
 return result;
}


void WCM_Database::retrieve()
{
 //void* db = wg_attach_existing_database("100");
 void* db = wg_attach_database("100", 0);
 char* fp = const_cast<char*>(full_path_.toStdString().c_str());
 wg_import_dump(db, fp);

 void* rec1 = wg_get_first_record(db);
 void* rec2 = wg_get_next_record(db, rec1);

 wg_int wgi = wg_get_field(db, rec2, 1);
 char* blob = wg_decode_blob(db, wgi);
 wg_int len = wg_decode_blob_len(db, wgi);

 qDebug() << " len: " << len;

 QByteArray qba(blob, len);

 QDataStream qds(&qba, QIODevice::ReadOnly);

 QString s1;

 qds >> s1;

 qDebug() << "STR: " << s1;

 int index;
 qds >> index;


 quintptr recptr; //= wg_encode_record(db, rec1);
 qds >> recptr;

 void* pv = wg_decode_record(db, recptr);

 //?qDebug() << " qpv1 " << qpv1;

// qDebug() << " 2 ";

// wg_query_arg arglist [2]; /* holds the arguments to the query */

// int column_code = 1;
// arglist[0].column = 0;
// arglist[0].cond = WG_COND_EQUAL;
// arglist[0].value = wg_encode_query_param_int(db, column_code);

// arglist[1].column = 1;
// arglist[1].cond = WG_COND_EQUAL;
// arglist[1].value = wg_encode_query_param_int(db, index);

   //? wg_find_record_int(db, 7, WG_COND_EQUAL, 443, NULL);

 //void* rec = wg_find_record_int(db, 0, WG_COND_EQUAL, 1, NULL);

   //
 //?wg_query* qry = (db, NULL, 0, arglist, 2);
 //?void* rec = wg_fetch(db, qry);


 //void* pv = reinterpret_cast<void*>(qpv1);

 //?qDebug() << " 3 " << pv;

//? wg_int wgi1 = wg_get_field(db, rec, 2);
 wg_int wgi1 = wg_get_field(db, pv, 2);

 //?qDebug() << " 4 " << pv;

 qDebug() << "STR: " << s1;

 char* qc = wg_decode_str(db, wgi1);

 qDebug() << "QC: " << qc;


// char* fp = const_cast<char*>(full_path.toStdString().c_str());
// wg_dump(db, fp);

}

template<>
wg_int WCM_Database::translate_data(wg_int data)
{
 return data;
}
template<>
wg_int WCM_Database::translate_data(quint64 data)
{
 return wg_encode_int(white_db_, (quint64) data);
}
template<>
wg_int WCM_Database::translate_data(char data)
{
 return wg_encode_char(white_db_, data);
}
template<>
wg_int WCM_Database::translate_data(double data)
{
 return wg_encode_double(white_db_, data);
}
template<>
wg_int WCM_Database::translate_data(QDate data)
{
 return wg_encode_int(white_db_, data.toJulianDay());
}
template<>
wg_int WCM_Database::translate_data(QDateTime data)
{
 return wg_encode_time(white_db_, data.toMSecsSinceEpoch());
}
template<>
wg_int WCM_Database::translate_data(QString data)
{
 char* cc = const_cast<char*>(data.toStdString().c_str());
 return  wg_encode_str(white_db_, cc, "EN");
}

wg_int WCM_Database::_add_column_entry_(WCM_Column* qc, wg_int data,
  u4& column_specific_record_index, u4& field_number)
{
 u4 record_specific_index;
 void* cer = create_column_entry_record(qc, record_specific_index);
 if(record_specific_index > 0) //qc->requires_record_specific_index())
 {
  qint8 fn = qc->get_record_index_field_number();
  wg_set_int_field(white_db_, cer, (int) fn, record_specific_index);
  column_specific_record_index = record_specific_index;
  ++column_change_count_;
 }
 else
 {
  column_specific_record_index = 0;
 }
 field_number = qc->get_effective_field_number();
 wg_int result = wg_set_field(white_db_, cer, field_number,  data);
 return result;
}

wg_int WCM_Database::_add_column_entry(WCM_Column* qc, wg_int data,
  u4& column_specific_record_index, u4& field_number)
{
 return _add_column_entry_(qc, data, column_specific_record_index, field_number);
}



//wg_int WCM_Database::_add_column_entry(WCM_Column* qc, wg_int data,
//  u4& column_specific_record_index, u4& field_number)
//{
// wg_int record_specific_index;
// void* cer = create_column_entry_record(qc, record_specific_index);
// if(record_specific_index > 0) //qc->requires_record_specific_index())
// {
//  qint8 fn = qc->get_record_index_field_number();
//  wg_set_int_field(white_db_, cer, (int) fn, record_specific_index);
//  column_specific_record_index = record_specific_index;
//  ++column_change_count_;
// }
// else
// {
//  column_specific_record_index = 0;
// }
// field_number = qc->get_effective_field_number();
// wg_int result = wg_set_field(white_db_, cer, field_number, data);
// return result;
//}

template<>
void WCM_Database::untranslate_data(wg_int data, wg_int& dt)
{
 dt = data;
}
template<>
void WCM_Database::untranslate_data(wg_int data, quint64& dt)
{
 wg_int result = wg_decode_int(white_db_, data);
 dt = result;
}
template<>
void WCM_Database::untranslate_data(wg_int data, char& dt)
{
 dt = wg_decode_char(white_db_, data);
}
template<>
void WCM_Database::untranslate_data(wg_int data, double& dt)
{
 dt = wg_decode_double(white_db_, data);
}
template<>
void WCM_Database::untranslate_data(wg_int data, QDate& dt)
{
 wg_int result = wg_decode_int(white_db_, data);
 dt = QDate::fromJulianDay(result);
}
template<>
void WCM_Database::untranslate_data(wg_int data, QDateTime& dt)
{
 wg_int result = wg_decode_int(white_db_, data);
 dt = QDateTime::fromMSecsSinceEpoch(result);
}
template<>
void WCM_Database::untranslate_data(wg_int data, QString& dt)
{
 char* result = wg_decode_str(white_db_, data);
 wg_int len = wg_decode_str_len(white_db_, data);
 std::string ss = std::string(result, len);
 dt = QString::fromStdString(ss);
}


template<>
wg_int WCM_Database::translate_data_to_query_param(int data)
{
 return wg_encode_query_param_int(white_db_, data);
}
template<>
wg_int WCM_Database::translate_data_to_query_param(quint64 data)
{
 return wg_encode_query_param_int(white_db_, (u4) data);
}
template<>
wg_int WCM_Database::translate_data_to_query_param(char data)
{
 return wg_encode_query_param_char(white_db_, data);
}
template<>
wg_int WCM_Database::translate_data_to_query_param(double data)
{
 return wg_encode_query_param_double(white_db_, data);
}
template<>
wg_int WCM_Database::translate_data_to_query_param(QDate data)
{
 return wg_encode_query_param_int(white_db_, data.toJulianDay());
}
template<>
wg_int WCM_Database::translate_data_to_query_param(QDateTime data)
{
 return wg_encode_query_param_int(white_db_, data.toMSecsSinceEpoch());
}
template<>
wg_int WCM_Database::translate_data_to_query_param(QString data)
{
 char* cc = const_cast<char*>(data.toStdString().c_str());
 return  wg_encode_query_param_str(white_db_, cc, "EN");
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



