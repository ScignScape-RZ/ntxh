
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef CLO_FILE__H
#define CLO_FILE__H


#include "phaong/phaong.h"
#include "phaong/phaong-types.h"

#include "global-types.h"

#include "kans.h"
#include "accessors.h"

#include <QVector>
#include <QString>

class QTextStream;

//class WCM_Hyponode;
//class WCM_Database;

class CLO_File
{
public:

 enum class Kinds
 {
  N_A, NPY_Logmelspec, NTXH_Logmelspec,
  NPY_MFCC, NTXH_MFCC, Audio
 };

 static QString kind_string(u1 k)
 {
  return kind_string((Kinds) k);
 }

 static QString kind_string(Kinds k)
 {
  switch(k)
  {
  case Kinds::N_A: return QString();
#define TEMP_MACRO(arg) case Kinds::arg: return #arg;
  TEMP_MACRO(NPY_Logmelspec)
  TEMP_MACRO(NPY_MFCC)
  TEMP_MACRO(NTXH_MFCC)
  TEMP_MACRO(Audio)
#undef TEMP_MACRO
   default: return QString();
  }
 }

private:

 Kinds kind_;
 QString abbreviation_;
 QString tail_;
 CLO_File* conversion_file_;
 QString absolute_path_;

public:

 CLO_File(Kinds k = Kinds::N_A);

 ACCESSORS(Kinds ,kind)
 ACCESSORS(QString ,abbreviation)
 ACCESSORS(QString ,tail)
 ACCESSORS(CLO_File* ,conversion_file)
 ACCESSORS(QString ,absolute_path)


};


#endif // CLO_FILE__H
