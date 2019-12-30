
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef STANDARD_GLYPHDECK_8B__H
#define STANDARD_GLYPHDECK_8B__H

#include "accessors.h"

#include "kans.h"

#include "glyphdeck-base-8b.h"

#include <QString>
#include <QList>
#include <QDate>

#include <functional>

//class WCM_WhiteDB;

KANS_(HTXN)

typedef quint8 u1;
typedef quint16 u2;

struct Glyph_Argument_Package;

class Standard_GlyphDeck_8b : public GlyphDeck_Base_8b
{
 u2 deck_id_;

 QChar get_text_default(u1 cue);

 QChar get_nondiacritic_default(u1 cue);

 QString get_nondiacritic_xdefault(u1 cue);
 
public:

 enum Alt_Interpretation_Codes {
   Space = 63,
   NpDot = 76, NsPer = 88, 
   NpExcX = 116,
   NpOParX = 117,
   NpCParX = 118,
   NpMinus = 74,
   SnDash = 81,
   DashSML = 82,
   DashX = 89,

   NmComX = 122,
   SqSqX = 102,
   TxtNumX = 109,
   TxtDolX = 110,
   TxtPerX = 111,
   TxtPlusX = 112,
   TxtAmpX = 113,
   SqDqX = 123,

   TxtStarX = 114,

   NpColX = 103,
   NpSemX = 104,
   NsQm = 89,
   NpQmX = 105,
   IndQm = 87,
   NsExc = 90,
   SnSp = 91,
   Boundary = 92,

   NpLtX = 120,
   NpGtX = 121,
   TxtEqX = 115,

   TxtAtX = 124,
   BslX = 106,
   TxtHatX = 100,

   NullX = 95,
   BqX = 125,

   OSqBrX = 91,
   CSqBrX = 92,
   OCyBrX = 93,
   CCyBrX = 94,

   PipeX = 107,
   TildeX = 126, 

   FslX = 90,
 };

 Standard_GlyphDeck_8b();

 ACCESSORS(u2 ,deck_id)

 void check_external(u1 gp, Glyph_Argument_Package& gap) Q_DECL_OVERRIDE;
 //?void check_external_excluding_numeral_diacritic(u1 gp, Glyph_Argument_Package& gap) Q_DECL_OVERRIDE;
 void get_latex(u1 gp, Glyph_Argument_Package& gap) Q_DECL_OVERRIDE;
 void get_latex_dia(u1 gp, Glyph_Argument_Package& gap) Q_DECL_OVERRIDE;
 void get_xml(u1 gp, Glyph_Argument_Package& gap) Q_DECL_OVERRIDE;
 void get_xml_dia(u1 gp, Glyph_Argument_Package& gap) Q_DECL_OVERRIDE;

 void get_nondiacritic_supplement(u1 cue, QString& result) Q_DECL_OVERRIDE;

 void get_qstring_out(u1 gp, Glyph_Argument_Package& gap) Q_DECL_OVERRIDE;

 void get_htxne_out(u1 gp, Glyph_Argument_Package& gap) Q_DECL_OVERRIDE;
// void get_htxne_dia(u1 gp, Glyph_Argument_Package& gap) Q_DECL_OVERRIDE;

// virtual void check_external(u1 gp, Glyph_Argument_Package& gap);
// virtual void get_latex(u1 gp, Glyph_Argument_Package& gap);
// virtual void get_latex_dia(u1 gp, Glyph_Argument_Package& gap);
// virtual void get_xml(u1 gp, Glyph_Argument_Package& gap);
// virtual void get_xml_dia(u1 gp, Glyph_Argument_Package& gap);

// virtual void get_qstring_out(u1 gp, Glyph_Argument_Package& gap);
};

_KANS(HTXN)

#endif // STANDARD_GLYPHDECK
