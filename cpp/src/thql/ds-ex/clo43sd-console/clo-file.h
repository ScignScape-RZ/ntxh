
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
  N_A, Logmelspec, MFCC, Audio
 };

private:

 Kinds kind_;
 QString abbreviation_;
 QString tail_;

public:

 CLO_File(Kinds k = Kinds::N_A);

 ACCESSORS(Kinds ,kind)
 ACCESSORS(QString ,abbreviation)
 ACCESSORS(QString ,tail)


};


#endif // CLO_FILE__H
