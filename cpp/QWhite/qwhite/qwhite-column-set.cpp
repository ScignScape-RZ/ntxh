 
#include "qwhite-column-set.h"

QWhite_Column_Set::QWhite_Column_Set(QWhite_Database& qwhite_db)
 : qwhite_db_(qwhite_db)
{

}

template<>
QWhite_Column_Set::QWhite_Column_As_Function_Object::QWhite_Column_Data_Package
  QWhite_Column_Set::QWhite_Column_As_Function_Object::operator ()(wg_enc rhs)
{
 return _as(rhs.data);
 //qwhite_db_.add_column_entry(column, rhs);
}

template<typename DATA_Type>
QWhite_Column_Set::QWhite_Column_As_Function_Object::QWhite_Column_Data_Package
  QWhite_Column_Set::QWhite_Column_As_Function_Object::operator ()(DATA_Type rhs)
{
 return as<DATA_Type>(rhs);
 //qwhite_db_.add_column_entry(column, rhs);
}

//template<typename DATA_Type>
//QWhite_Column_Data_Package operator ()(DATA_Type rhs);
//  {
//   return as<DATA_Type>(rhs);

//   //qwhite_db_.add_column_entry(column, rhs);
//  }


//QWhite_Column_Set::QWhite_Column_As_Function_Object QWhite_Column_Set::operator[](std::string cn)
//{
// return operator [](QString::fromStdString(cn));
//}

void QWhite_Column_Set::use_columns(QStringList column_names)
{
 for(QString cn : column_names)
 {
  QWhite_Column* qc = qwhite_db_.get_column_by_name(cn);
  if(qc)
  {
   column_by_name_[cn] = qc;
  }
 }
}


QWhite_Column_Set::QWhite_Column_As_Function_Object
  QWhite_Column_Set::operator[](QString column_name)
{
 QWhite_Column* qc = qwhite_db_.get_column_by_name(column_name);
 if(qc)
 {
  return {qwhite_db_, qc};
 }
 throw QWhite_Unrecognized_Column_Exception();
}

QWhite_Column_Set::QWhite_Column_Data_Holder
  QWhite_Column_Set::operator()(QString column_name)
{
 QWhite_Column* qc = qwhite_db_.get_column_by_name(column_name);
 if(qc)
 {
  return {qwhite_db_, qc, 0};
 }
 throw QWhite_Unrecognized_Column_Exception();
}

