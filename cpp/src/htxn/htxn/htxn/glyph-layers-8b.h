
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef GLYPH_LAYERS_8B__H
#define GLYPH_LAYERS_8B__H

#include "accessors.h"

#include "kans.h"

#include <QString>
#include <QList>
#include <QVector>

#include <functional>

//class WCM_WhiteDB;

KANS_(HTXN)

typedef quint8 u1;
typedef quint32 u4;
typedef quint64 u8;

class GlyphDeck_Base_8b;
class Glyph_Vector_8b;

class Glyph_Layers_8b : public QVector<Glyph_Vector_8b*>
{
 QVector<GlyphDeck_Base_8b*> decks_by_id_;

public:

 void get_latex(u4 layer, u4 index, Glyph_Argument_Package& gap);

 void get_qstring_out(Glyph_Vector_8b& gv, 
   u4 index, Glyph_Argument_Package& gap);

 //virtual void check_external(u1 gp, Glyph_Argument_Package& gap); 

};

_KANS(HTXN)

#endif // GLYPH_VECTOR_8B__H
