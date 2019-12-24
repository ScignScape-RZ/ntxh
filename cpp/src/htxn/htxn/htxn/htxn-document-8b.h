
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef HTXN_DOCUMENT_8B__H
#define HTXN_DOCUMENT_8B__H

#include "accessors.h"

#include "kans.h"

#include "htxn-layers-8b.h"

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

class HTXN_Document_8b : public Glyph_Layers_8b
{
 u4 current_deck_code_;
 GlyphDeck_Base_8b* current_deck_;

 Glyph_Vector_8b* current_glyph_vector_;

public:

 HTXN_Document_8b();

// ACCESSORS_SET(GlyphDeck_Base_8b* ,current_deck)

 void add_standard_deck();

 void read_layer(QString text);
 void encode_latin1(const QByteArray& src, Glyph_Vector_8b& target);

 void get_qstring_out(u4 layer, QString& result);

 void read_glyph_point(Glyph_Argument_Package& gap, 
   u4 index, Glyph_Vector_8b& gv)


};

_KANS(HTXN)

#endif // GLYPH_VECTOR_8B__H
