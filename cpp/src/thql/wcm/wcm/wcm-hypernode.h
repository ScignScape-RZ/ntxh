
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef WCM_HYPERNODE__H
#define WCM_HYPERNODE__H

#include "accessors.h"

#include <QString>
#include <QList>
#include <QDate>

#include <functional>

class WCM_Column_Set;
class WCM_Hyponode;
class WCM_Type;
class WCM_Database;
//class WCM_WhiteDB;

class WCM_Hypernode
{
 struct With_Hyponode_Package
 {
  WCM_Hyponode* who;
  WCM_Database* wcdb;
  void operator<< (std::function<void (WCM_Hyponode&)> fn)
  {
   fn(*who);
  }
//  void operator<< (std::function<void (WCM_Hyponode&, WCM_WhiteDB& wdb)> fn)
//  {
//   fn(*who, wdb);
//  }
 };

 struct Add_Hyponodes_Package
 {
  WCM_Hypernode* _this;
  WCM_Hyponode** whos;
  void operator[] (quint32 size)
  {
   _this->add_hyponodes(whos, size);
  }
  void operator() (quint32 size)
  {
   _this->add_hyponodes(whos, size);
   delete [] whos;
  }
 };

 QVector<WCM_Hyponode*> hyponodes_;

 WCM_Type* wcm_type_;

 QMap<quint32, QString>* indexed_column_map_;

 QPair<QString, QString>* test_;


public:

 ACCESSORS__RGET(QVector<WCM_Hyponode*> ,hyponodes)
 ACCESSORS(WCM_Type* ,wcm_type)
// ACCESSORS__GET(PASTE_EXPRESSION(QMap<quint32, QString*>)* ,indexed_column_map)
// ACCESSORS__SET(PASTE_EXPRESSION(QMap<quint32, QString*>)* ,indexed_column_map)

 ACCESSORS(MACRO_PASTE(QMap<quint32, QString>)* ,indexed_column_map)

 ACCESSORS(MACRO_PASTE(QPair<QString, QString>)* ,test)


 WCM_Hypernode();

 With_Hyponode_Package with_hyponode(quint32 index);

 void supply_data(QByteArray& qba, WCM_Column_Set& columns);
 void absorb_data(const QByteArray& qba, WCM_Column_Set& columns);

//?
// void supply_data(QByteArray& qba);
// void absorb_data(const QByteArray& qba);

 quint32 add_to_database(WCM_Database& wcmd, QString type_col, QString col);

 void add_hyponode(WCM_Hyponode* who);
 void add_hyponodes(QList<WCM_Hyponode*> whos);
 Add_Hyponodes_Package add_hyponodes(WCM_Hyponode** whos)
 {
  return {this, whos};
 }

 void add_hyponodes(WCM_Hyponode** whos, quint32 size);

 void each_hyponode(std::function<void(WCM_Hypernode&, WCM_Hyponode&, quint32)>);
 void each_hyponode(std::function<void(WCM_Hyponode&, quint32)>);
 void each_hyponode(std::function<void(WCM_Hypernode&, WCM_Hyponode&)>);
 void each_hyponode(std::function<void(WCM_Hyponode&)>);

 QString check_column(quint32 index);


};

#endif //  WCM_HYPERNODE__H


