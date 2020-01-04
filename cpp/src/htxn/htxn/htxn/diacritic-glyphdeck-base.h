
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef DIACRITIC_GLYPHDECK_BASE__H
#define DIACRITIC_GLYPHDECK_BASE__H

#include "accessors.h"

#include "kans.h"

#include <QString>
#include <QList>
#include <QDate>

#include <functional>


KANS_(HTXN)

typedef quint8 u1;
typedef quint16 u2;

class Diacritic_GlyphDeck_Base
{
 virtual void get_full_htxne_representation
  (u2 gp, QChar cue, QChar& rep, QString& full_rep) = 0;
};


#endif // DIACRITIC_GLYPHDECK_BASE__H
