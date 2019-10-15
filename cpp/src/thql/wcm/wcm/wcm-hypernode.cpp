
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "wcm-hypernode.h"

#include "wcm-hyponode.h"

#include <QDataStream>
#include <QIODevice>

#include "wcm/wcm-column-set.h"

typedef long wg_int;

WCM_Hypernode::WCM_Hypernode()
  :  indexed_column_map_(nullptr)
{

}

void WCM_Hypernode::add_hyponode(WCM_Hyponode* who)
{
 hyponodes_.push_back(who); 
}

void WCM_Hypernode::add_hyponodes(QList<WCM_Hyponode*> whos)
{
 hyponodes_.append(whos.toVector());
}

QString WCM_Hypernode::check_column(quint32 index)
{
 return indexed_column_map_? indexed_column_map_->value(index): QString();
}

void WCM_Hypernode::add_hyponodes(WCM_Hyponode** whos, quint32 size)
{
 int sz = hyponodes_.size();
 hyponodes_.resize(sz + size);
 int i = 0;
 std::for_each(hyponodes_.begin() + sz,
   hyponodes_.end(), [whos, &i](WCM_Hyponode*& who)
 {
  who = whos[i];
  ++i;
 });
}

quint32 WCM_Hypernode::add_to_database(WCM_Database& wcmd,
  QString type_col, QString col)
{
 WCM_Column_Set qwcs(wcmd);
 QByteArray qba;
 supply_data(qba, qwcs);
 quint32 record_index;
 wcmd.add_record(type_col, col, qba, record_index);
 return record_index;
}

void WCM_Hypernode::supply_data(QByteArray& qba, WCM_Column_Set& columns)
{
 QDataStream qds(&qba, QIODevice::WriteOnly);

 quint32 sz = hyponodes_.size();
 qds << sz;

 if(indexed_column_map_)
 {
  each_hyponode([&qds, &columns](WCM_Hypernode& _this, WCM_Hyponode& who, quint32 index)
  {
   QString col = _this.check_column(index);
   if(col.isEmpty())
   {
    qds << who;
   }
   else
   {
    qds << columns[col](who.wgdb_encoding());
   }  
  });
 }
 else
 {
  each_hyponode([&qds](WCM_Hyponode& who)
  {
   qds << who;  
  });
 }

// qds << columns["Patient::Id"](patient_id_);
// qds << columns["Patient::Name"](name_);
}

void WCM_Hypernode::absorb_data(const QByteArray& qba, WCM_Column_Set& columns)
{
 QDataStream qds(qba);

 quint32 sz;
 qds >> sz;

 hyponodes_.resize(sz);

 if(indexed_column_map_)
 {
  for(int i = 0; i < sz; ++i)
  {
   WCM_Hyponode* who = new WCM_Hyponode;
   QString col = indexed_column_map_->value(i);
   if(col.isEmpty())
     qds >> *who;
   else
   {
    qds >> columns(col)(*who);
   }
   hyponodes_[i] = who;
  }
 }
 else
 {
  for(int i = 0; i < sz; ++i)
  {
   WCM_Hyponode* who = new WCM_Hyponode;
   qds >> *who;
   hyponodes_[i] = who;
  }
 }

// qds >> columns("Patient::Id")(patient_id_); //(patient_id_);
// qds >> columns("Patient::Name")(name_); //(name_);
}

WCM_Hypernode::With_Hyponode_Package WCM_Hypernode::with_hyponode(quint32 index)
{
 return {hyponodes_.value(index)};
}


void WCM_Hypernode::each_hyponode(std::function<void(WCM_Hypernode&, WCM_Hyponode&, quint32)> fn)
{
 quint32 i = 0;
 for(WCM_Hyponode* who : hyponodes_)
 {
  fn(*this, *who, i);
  ++i;
 }
}

void WCM_Hypernode::each_hyponode(std::function<void(WCM_Hyponode&, quint32)> fn)
{
 quint32 i = 0;
 for(WCM_Hyponode* who : hyponodes_)
 {
  fn(*who, i);
  ++i;
 }
}

void WCM_Hypernode::each_hyponode(std::function<void(WCM_Hypernode&, WCM_Hyponode&)> fn)
{
 for(WCM_Hyponode* who : hyponodes_)
 {
  fn(*this, *who);
 }
}

void WCM_Hypernode::each_hyponode(std::function<void(WCM_Hyponode&)> fn)
{
 for(WCM_Hyponode* who : hyponodes_)
 {
  fn(*who);
 }
}


