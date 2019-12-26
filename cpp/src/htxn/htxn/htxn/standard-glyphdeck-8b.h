
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

// virtual void check_external(u1 gp, Glyph_Argument_Package& gap);
// virtual void get_latex(u1 gp, Glyph_Argument_Package& gap);
// virtual void get_latex_dia(u1 gp, Glyph_Argument_Package& gap);
// virtual void get_xml(u1 gp, Glyph_Argument_Package& gap);
// virtual void get_xml_dia(u1 gp, Glyph_Argument_Package& gap);

// virtual void get_qstring_out(u1 gp, Glyph_Argument_Package& gap);
};

_KANS(HTXN)

#endif // STANDARD_GLYPHDECK
