
#include "wcm-database.h"
#include "wcm-column.h"

#include "wcm-hyponode.h"

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
 for(quint32 i = 0; i < size; ++i)
 {
  result[i] = new WCM_Hyponode;
 }
 return result;
}

WCM_Hyponode** WCM_Database::New_Hyponode_Array_Package::operator <<
  (std::function<void(WCM_WhiteDB&, WCM_Hyponode*, quint32)> fn)
{
 WCM_Hyponode** result = new WCM_Hyponode* [size];
 for(quint32 i = 0; i < size; ++i)
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
 quint32 code;
 lhs >> code;
 rhs->set_database_column_code(code);
 quint32 record_count;
 lhs >> record_count;
 rhs->set_record_count(record_count);
 return lhs;
}

QDataStream& operator >>(QDataStream& lhs, QVector<WCM_Column*>& rhs)
{
 quint32 len;
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
//    s << quint32(v.size());
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


quint32 WCM_Database::new_column_code()
{
 return max_column_code_ + 1;
}

void WCM_Database::confirm_new_column_code(quint32 id)
{
 max_column_code_ = id;
 wg_set_field(white_db_, max_column_code_record_, 0, wg_encode_int(white_db_, max_column_code_));
}

//void WCM_Database::init_columns(QByteArray& qba)
//{
// QDataStream qds(&qba, QIODevice::ReadOnly);
// quint32 len;
// qds >> len;
// qds >> columns_;
//}

void WCM_Database::init_columns()
{
 max_column_code_record_ = wg_get_first_record(white_db_);
 wg_int wgi = wg_get_field(white_db_, max_column_code_record_, 0);
 max_column_code_ = wg_decode_int(white_db_, wgi);
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

void WCM_Database::check_create()
{
 char* np = const_cast<char*>(name_.toStdString().c_str());
 white_db_ = wg_attach_existing_database(np);

 if(white_db_)
 {
  init_columns();
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
  }
  else
  {
   // //  Start from scratch as a last resort.
   create();
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

void* WCM_Database::retrieve_column_entry_value(WCM_Column* qc, quint32 record_id, wg_int& result_value)
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


void* WCM_Database::retrieve_record(QByteArray& qba, QString archive_name,
  QString index_column_name, wg_int query_param)
{
 //? wg_find_record_int(db, 7, WG_COND_EQUAL, 443, NULL);

 // wg_query_arg arglist [2]; /* holds the arguments to the query */

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

  wg_query* qry = wg_make_query(white_db_, NULL, 0, arglist, 2);

  void* index_record = wg_fetch(white_db_, qry);
  if(index_record)
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
  }
 }
 else
 {
  result = nullptr;
 }
 return result;
}


void* WCM_Database::create_column_entry_record(WCM_Column* qc,
  wg_int& record_specific_index, int field_count) //, wg_int column_id)
{
 void* result = wg_create_record(white_db_, field_count);
 wg_set_field(white_db_, result, 0, wg_encode_int(white_db_, qc->database_column_code()));
 record_specific_index = qc->get_next_record_index();
 return result;
}

void* WCM_Database::add_record(QString type_column, QString archive_column,
  const QByteArray& qba, quint32& record_index)
{
 WCM_Column* qc = get_column_by_name(archive_column);
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
 wg_int ri;
 void* result = create_column_entry_record(qc, ri, 3);
 record_index = ri;

 int index_col = qc->get_record_index_field_number();
 wg_set_field(white_db_, result, index_col,
   wg_encode_int(white_db_, ri));

 int fn = qc->get_effective_field_number();

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

WCM_Column* WCM_Database::create_new_column(QString name)
{
 quint32 id = new_column_code();
 WCM_Column* result = new WCM_Column(name, id);
 if(result)
 {
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
 //?wg_query* qry = wg_make_query(db, NULL, 0, arglist, 2);
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
  quint32& column_specific_record_index, quint32& field_number)
{
 wg_int record_specific_index;
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
  quint32& column_specific_record_index, quint32& field_number)
{
 return _add_column_entry_(qc, data, column_specific_record_index, field_number);
}



//wg_int WCM_Database::_add_column_entry(WCM_Column* qc, wg_int data,
//  quint32& column_specific_record_index, quint32& field_number)
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
 return wg_encode_query_param_int(white_db_, (quint32) data);
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



