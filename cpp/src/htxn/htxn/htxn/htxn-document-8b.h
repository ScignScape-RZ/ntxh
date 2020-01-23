
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef HTXN_DOCUMENT_8B__H
#define HTXN_DOCUMENT_8B__H

#include "accessors.h"

#include "global-types.h"

#include "kans.h"

#include "glyph-layers-8b.h"

#include <QString>
#include <QList>
#include <QVector>

#include <functional>

#include "graph/htxn-node-details.h"

//class WCM_WhiteDB;

KANS_(HTXN)

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

 Glyph_Layer_8b* read_layer(QString text, u2 offset = 0);
 void read_layer(Glyph_Layer_8b* gl, QString text, u2 offset = 0);


 Glyph_Layer_8b* add_layer();

 void check_pre_space_append(QString& text, const HTXN_Node_Detail& nd);

 void encode_latin1(const QByteArray& src, Glyph_Vector_8b& target, u2 offset);

 void encode_latin1(QByteArray& src, Glyph_Vector_8b& target,
   u4 index, u4& last_index, 
   Glyph_Vector_8b* offset_acc = nullptr, QIODevice* qiod = nullptr, 
   u4 buffer_length = 0);

 u4 add_detail_range(Glyph_Layer_8b* layer, u4 enter, u4 leave, 
   HTXN_Node_Detail::Wrap_Mode_Indicator_Codes wmic,  
   u2 whitespace_code = 0);
 u4 add_detail_range_region(Glyph_Layer_8b* layer, u4 enter, u4 leave,
   HTXN_Node_Detail::Wrap_Mode_Indicator_Codes wmic, 
   u2 whitespace_code = 0);
 u4 add_detail_range_optional(Glyph_Layer_8b* layer, u4 enter, u4 leave,
   HTXN_Node_Detail::Wrap_Mode_Indicator_Codes wmic, 
   u2 whitespace_code = 0);

 void tie_detail_range_preempt(u4 rc1, u4 rc2);

 void check_precedent_ranges(const HTXN_Node_Detail& nd,
   QVector<QPair<HTXN_Node_Detail*, QString>>& result,
   Glyph_Layer_8b* calling_layer);

 void get_qstring_out(u4 layer, QString& result);
 void get_htxne_out(u4 layer, QByteArray& result);
 void get_htxne_out(u4 layer, QString& result);
 void get_htxne_out(Glyph_Vector_8b* gv, QByteArray& result);

 void write_htxne_out(QIODevice& qiod);
 void read_htxne_in(QIODevice& qiod);

 void write_latex_out(QTextStream& qts);

 void get_latex_out(u4 layer, QString& result);

 void get_latex_out(Glyph_Layer_8b* gl, 
   u4 enter, u4 leave, QString& result, HTXN_Node_Detail* nd = nullptr);

 void get_latex_insert(HTXN_Node_Detail* nd,
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

 void mark_last_as_environment_main_tile(u4 ref);


 QString check_latex_insert(Glyph_Layer_8b& gl,
   u4 index, Glyph_Argument_Package& cmdgap, 
   QVector<QPair<HTXN_Node_Detail*, QString>>& precs, QStringList& succs, QString& result);

};

_KANS(HTXN)

#endif // HTXN_DOCUMENT_8B__H

