
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef GLOBAL_TYPES__H
#define GLOBAL_TYPES__H

#include <QtGlobal>
#include <QString>
#include <QMap>

#include <functional>

typedef quint8 u1;
typedef quint16 u2;
typedef quint32 u4;
typedef quint64 u8;

typedef qint8 s1;
typedef qint16 s2;
typedef qint32 s4;
typedef qint64 s8;

static inline QString operator ""_q(const char* cs, size_t size)
{
 std::string ss(cs, size);
 return QString::fromStdString(ss);
}

#endif // GLOBAL_TYPES__H