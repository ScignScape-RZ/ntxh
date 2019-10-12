
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

#endif // WITHS__H
