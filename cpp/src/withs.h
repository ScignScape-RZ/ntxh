
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef WITHS__H
#define WITHS__H

#include <QtGlobal>
#include <QString>
#include <QMap>
#include <QDir>

#include <functional>


template<typename KEY_Type, typename VAL_Type>
struct with_map_Package
{
 QMap<KEY_Type, VAL_Type>& qm;
 void operator<<(std::function<void(const KEY_Type&, const VAL_Type&)> fn)
 {
  QMapIterator<KEY_Type, VAL_Type> it(qm);
  while (it.hasNext())
  {
   it.next();
   fn(it.key(), it.value());
  }
 }
};

template<typename KEY_Type, typename VAL_Type>
static inline with_map_Package<KEY_Type, VAL_Type>
  with_map(QMap<KEY_Type, VAL_Type>& qm)
{
 return {qm};
}


struct with_files_Package
{
 QDir qd;
 QStringList filters;
 QDir::Filters qdfilters;
 with_files_Package& filter(QStringList&& qsl)
 {
  filters = qsl;
  return *this;
 }
 with_files_Package& filter(const QStringList& qsl)
 {
  filters = qsl;
  return *this;
 }
 void operator<<(std::function<void(QFileInfo&)> fn)
 {
  QFileInfoList qfil;
  if(filters.isEmpty())
    qfil = qd.entryInfoList(qdfilters);
  else
    qfil = qd.entryInfoList(filters, qdfilters);

  for(QFileInfo qfi :  qfil)
  {
   fn(qfi);
  }
 }
};

with_files_Package with_files(QDir qd)
{
 return {qd, {}, QDir::Files | QDir::NoDotAndDotDot};
}


// template<typename T>

struct wr_brake
{
 std::function<void(wr_brake)> fn;
 quint8 code;
 static std::function<void(wr_brake)> get_null()
 {
  static std::function<void(wr_brake)> the_null = [](wr_brake){};
  return the_null;
 }
 wr_brake() : fn(wr_brake::get_null()), code(0)
 {
 }
 wr_brake(std::function<void(wr_brake)> f) : fn(f), code(1)
 {
 }

};

struct with_range_2_Package
{
 quint32 min;
 quint32 max;

 void operator<<(std::function<void(quint32)> fn)
 {
  for(quint32 i = min; i < max; ++i)
    fn(i);
 }

 void operator<<(std::function<void(quint32, wr_brake wrb)> fn)
 {
  auto null_wrb = wr_brake::get_null();
  auto wrb = [&null_wrb](wr_brake w)
  {
   if(w.code == 1)
     w.fn({});
   null_wrb = nullptr;
  };
  for(quint32 i = min; i < max; ++i)
  {
   fn(i, {wrb});
   if(!null_wrb)
     break;
  }
 }

};

struct with_range_Package
{
 quint32 min;
 with_range_2_Package operator()(quint32 max)
 {
  return {min, max};
 }
 with_range_2_Package operator[](quint32 max)
 {
  return {min, max + 1};
 }
};

with_range_Package with_range(quint32 min)
{
 return {min};
}



#endif // WITHS__H
