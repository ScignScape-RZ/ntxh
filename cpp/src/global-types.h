
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

template<typename T>
struct Defaulting_To_Zero
{
 T the_t;
 Defaulting_To_Zero(T tt) : the_t(tt){}
 Defaulting_To_Zero() : the_t(0){}
 operator T() { return the_t; }

 bool operator*()
 {
  return !is_max();
 }

 static Defaulting_To_Zero<T> get_max()
 {
  return Defaulting_To_Zero(std::numeric_limits<T>::max());
 }

 bool is_max()
 {
  return the_t == std::numeric_limits<T>::max();
 }

// operator bool()
// {
//  return the_t != -1;
// }
};

typedef Defaulting_To_Zero<u1> z1;
typedef Defaulting_To_Zero<u2> z2;
typedef Defaulting_To_Zero<u4> z4;
typedef Defaulting_To_Zero<u8> z8;


//#define until(x) return ({x}).inv;


#endif // GLOBAL_TYPES__H
