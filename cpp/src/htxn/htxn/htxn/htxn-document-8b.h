
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef HTXN_DOCUMENT_8B__H
#define HTXN_DOCUMENT_8B__H

#include "accessors.h"

#include "kans.h"

#include "glyph-layers-8b.h"

#include <QString>
#include <QList>
#include <QVector>

#include <functional>

#include "graph/htxn-node-details.h"

//class WCM_WhiteDB;

KANS_(HTXN)

typedef quint8 u1;
typedef quint16 u2;
typedef quint32 u4;
typedef quint64 u8;

class GlyphDeck_Base_8b;
class Glyph_Vector_8b;
class Standard_Diacritic_GlyphDeck;

class HTXN_Document_8b : public Glyph_Layers_8b, 
  public HTXN_Node_Details
{
 u4 current_deck_code_;
 GlyphDeck_Base_8b* current_deck_;
 Standard_Diacritic_GlyphDeck* current_diacritic_deck_;

 Glyph_Vector_8b* current_glyph_vector_;

public:

 HTXN_Document_8b();

// ACCESSORS_SET(GlyphDeck_Base_8b* ,current_deck)

// void add_range(Glyph_Layer_8b* gl, u4 enter, u4 leave);

 void add_standard_deck();
 void add_standard_diacritic_deck();

 Glyph_Layer_8b* read_layer(QString text, u2 gap = 0);

 void encode_latin1(const QByteArray& src, Glyph_Vector_8b& target, u2 gap);
 void encode_latin1(const QByteArray& src, Glyph_Vector_8b& target,
   u4 index, u4& last_index);

 u4 add_detail_range(Glyph_Layer_8b* layer, u4 enter, u4 leave);
 u4 add_detail_range_region(Glyph_Layer_8b* layer, u4 enter, u4 leave);

 void tie_detail_range_preempt(u4 rc1, u4 rc2);

 void check_precedent_ranges(const HTXN_Node_Detail& nd, QStringList& result);

 void get_qstring_out(u4 layer, QString& result);
 void get_htxne_out(u4 layer, QByteArray& result);
 void get_htxne_out(u4 layer, QString& result);

 void get_latex_out(u4 layer, QString& result);
 void get_latex_out(Glyph_Layer_8b* gl, 
   u4 enter, u4 leave, QString& result);

 void get_latex_insert(HTXN_Node_Detail& nd,
  QString& result);

 void get_latex_command(Glyph_Layer_8b& gl, u4 enter, u4 leave,
   Glyph_Argument_Package& gap, QString& result); 

 void read_glyph_point(Glyph_Argument_Package& gap, 
   u4 index, Glyph_Vector_8b& gv);

 u1 get_diacritic_length_or_code(char cue, u2& code);
 u2 get_diacritic_code(char cue, u1 scope);
 u2 get_diacritic_cue_code(char cue);
 u2 get_diacritic_code_inh(u1 pos, u1 length);

 void mark_diacritic_code(Glyph_Vector_8b& target, u4 index, u2 diacritic_code);

 QString check_latex_insert(Glyph_Layer_8b& gl,
   u4 index, Glyph_Argument_Package& cmdgap, 
   QStringList& precs, QStringList& succs, QString& result);

};

_KANS(HTXN)

#endif // HTXN_DOCUMENT_8B__H

