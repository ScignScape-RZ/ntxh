
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef GLYPHDECK_BASE_8B__H
#define GLYPHDECK_BASE_8B__H

#include "accessors.h"

#include "kans.h"

#include <QString>
#include <QList>
#include <QDate>

#include <functional>

//class WCM_WhiteDB;

KANS_(HTXN)

typedef quint8 u1;
typedef quint16 u2;

struct Glyph_Argument_Package; 

class GlyphDeck_Base_8b
{
protected:
 u2 deck_id_;
 
public:

 GlyphDeck_Base_8b();

 ACCESSORS(u2 ,deck_id)

// QChar get_latex(u1 gp, QString& extra);
// QChar get_xml(u1 gp, QString& extra);
// u1 get_diacritic_code(u1 gp);

 virtual void check_external(u1 gp, Glyph_Argument_Package& gap) = 0;
 virtual void check_external_excluding_numeral_diacritic(u1 gp, Glyph_Argument_Package& gap) = 0;
 virtual void get_latex(u1 gp, Glyph_Argument_Package& gap) = 0;
 virtual void get_latex_dia(u1 gp, Glyph_Argument_Package& gap) = 0;
 virtual void get_xml(u1 gp, Glyph_Argument_Package& gap) = 0;
 virtual void get_xml_dia(u1 gp, Glyph_Argument_Package& gap) = 0;

 virtual void get_qstring_out(u1 gp, Glyph_Argument_Package& gap) = 0;
};

_KANS(HTXN)

#endif // GLYPHDECK_BASE_8B__H
