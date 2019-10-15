
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "wcm-column-set.h"

WCM_Column_Set::WCM_Column_Set(WCM_Database& wcm_db)
 : wcm_db_(wcm_db)
{

}

template<>
WCM_Column_Set::WCM_Column_As_Function_Object::WCM_Column_Data_Package
  WCM_Column_Set::WCM_Column_As_Function_Object::operator ()(wg_enc rhs)
{
 return _as(rhs.data);
 //wcm_db_.add_column_entry(column, rhs);
}

template<typename DATA_Type>
WCM_Column_Set::WCM_Column_As_Function_Object::WCM_Column_Data_Package
  WCM_Column_Set::WCM_Column_As_Function_Object::operator ()(DATA_Type rhs)
{
 return as<DATA_Type>(rhs);
 //wcm_db_.add_column_entry(column, rhs);
}

//template<typename DATA_Type>
//WCM_Column_Data_Package operator ()(DATA_Type rhs);
//  {
//   return as<DATA_Type>(rhs);

//   //wcm_db_.add_column_entry(column, rhs);
//  }


//WCM_Column_Set::WCM_Column_As_Function_Object WCM_Column_Set::operator[](std::string cn)
//{
// return operator [](QString::fromStdString(cn));
//}

void WCM_Column_Set::use_columns(QStringList column_names)
{
 for(QString cn : column_names)
 {
  WCM_Column* qc = wcm_db_.get_column_by_name(cn);
  if(qc)
  {
   column_by_name_[cn] = qc;
  }
 }
}


WCM_Column_Set::WCM_Column_As_Function_Object
  WCM_Column_Set::operator[](QString column_name)
{
 WCM_Column* qc = wcm_db_.get_column_by_name(column_name);
 if(qc)
 {
  return {wcm_db_, qc};
 }
 throw WCM_Unrecognized_Column_Exception();
}

WCM_Column_Set::WCM_Column_Data_Holder
  WCM_Column_Set::operator()(QString column_name)
{
 WCM_Column* qc = wcm_db_.get_column_by_name(column_name);
 if(qc)
 {
  return {wcm_db_, qc, 0};
 }
 throw WCM_Unrecognized_Column_Exception();
}

