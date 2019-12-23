
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "standard-glyphdeck-8b.h"

#include "standard-glyphpack-8b.h"


USING_KANS(HTXN)

Standard_GlyphDeck_8b::Standard_GlyphDeck_8b()
 :  deck_id_(0)
{

}

void Standard_GlyphDeck_8b::check_external(u1 gp, Glyph_Argument_Package& gap)
{
 if( (gp & 128) > 0 )
 {
  gap.flags.maybe_external_deck = true;
  gap.glyph_code = (u8) gp & 127;   
  return;
 }
 if( (gp & 64) > 0 )
 {
  gap.flags.maybe_external_diacritic = true;
  gap.glyph_code = (u8) gp & 63;   
  return;
 } 
}


QChar Standard_GlyphDeck_8b::get_text_default(u1 cue)
{
 switch(cue)
 {
 case 0: return QChar('0');
 case 1: return QChar('1');
 case 2: return QChar('2');
 case 3: return QChar('3');
 case 4: return QChar('4');
 case 5: return QChar('5');
 case 6: return QChar('6');
 case 7: return QChar('7');
 case 8: return QChar('8');
 case 9: return QChar('9');
 case 10: return QChar('a');
 case 11: return QChar('b');
 case 12: return QChar('c');
 case 13: return QChar('d');
 case 14: return QChar('e');
 case 15: return QChar('f');
 case 16: return QChar('g');
 case 17: return QChar('h');
 case 18: return QChar('i');
 case 19: return QChar('j');
 case 20: return QChar('k');
 case 21: return QChar('l');
 case 22: return QChar('m');
 case 23: return QChar('n');
 case 24: return QChar('o');
 case 25: return QChar('p');
 case 26: return QChar('q');
 case 27: return QChar('r');
 case 28: return QChar('s');
 case 29: return QChar('t');
 case 30: return QChar('u');
 case 31: return QChar('v');
 case 32: return QChar('w');
 case 33: return QChar('x');
 case 34: return QChar('y');
 case 35: return QChar('z');
 case 36: return QChar('A');
 case 37: return QChar('B');
 case 38: return QChar('C');
 case 39: return QChar('D');
 case 40: return QChar('E');
 case 41: return QChar('F');
 case 42: return QChar('G');
 case 43: return QChar('H');
 case 44: return QChar('I');
 case 45: return QChar('J');
 case 46: return QChar('K');
 case 47: return QChar('L');
 case 48: return QChar('M');
 case 49: return QChar('N');
 case 50: return QChar('O');
 case 51: return QChar('P');
 case 52: return QChar('Q');
 case 53: return QChar('R');
 case 54: return QChar('S');
 case 55: return QChar('T');
 case 56: return QChar('U');
 case 57: return QChar('V');
 case 58: return QChar('W');
 case 59: return QChar('X');
 case 60: return QChar('Y');
 case 61: return QChar('Z');
 case 62: return QChar('_');
 case 63: return QChar('-');
 default: return QChar(); 
 }
}

QString Standard_GlyphDeck_8b::get_nondiacritic_xdefault_latex(u1 cue)
{
 switch(cue)
 {
 case 0: return QString();
 case 1: return QString();
 case 2: return QString("{\\DLi}");
 case 3: return QString("{\\DLj});
 case 4: return QString("{\\dqDCe}");
 case 5: return QString("{\\dqDCl}");
 case 6: return QString("{\\sqDCe}");
 case 7: return QString("{\\sqDCl}");
 case 8: return QString("{\\emDCe}");
 case 9: return QString("{\\emDCl}");
 case 10: return QString("{\\bfDCe}");
 case 11: return QString("{\\bfDCl}");
 case 12: return QString("{\\ulDCe}");
 case 13: return QString("{\\ulDCl}");
 case 14: return QString("{\\dcIne}");
 case 15: return QString("{\\dcInl}");
 case 16: return QString("{\\dcAve}");
 case 17: return QString("{\\dcAvl}");
 case 18: return QString("{\\dcIAe}");
 case 19: return QString("{\\dcIAl}");
 case 20: return QString("{\\dcHve}");
 case 21: return QString("{\\dcHvl}");
 case 22: return QString("{\\sDiv}");
 case 23: return QString("{\\mDiv}");
 case 24: return QString("{\\lDiv}");
 case 25: return QString("{\\emD}");
 case 26: return QString("{\\enD}");
 case 27: return QString("{\\num}");
 case 28: return QString("{\\dol}");
 case 29: return QString("{\\prc}");
 case 30: return QString("{\\amp}");
 case 31: return QString("{\\sct}");
 default: return QChar(); 
}

#ifdef HIDE
 case 4: return QString("{\\dqIne}");
 case 5: return QString("{\\dqInl}");
 case 6: return QString("{\\dqAve}");
 case 7: return QString("{\\dqAvl}");
 case 8: return QString("{\\dqHve}");
 case 9: return QString("{\\dqHvl}");
 case 10: return QString("{\\dqIAe}");
 case 11: return QString("{\\dqIAl}");
 case 12: return QString("{\\sqIne}");
 case 13: return QString("{\\sqInl}");
 case 14: return QString("{\\sqAve}");
 case 15: return QString("{\\dqAvl}");
 case 16: return QString("{\\sqHve}");
 case 17: return QString("{\\sqHvl}");
 case 18: return QString("{\\sqIAe}");
 case 19: return QString("{\\sqIAl}");
#endif // HIDE

QChar Standard_GlyphDeck_8b::get_nondiacritic_default(u1 cue)
{
 switch(cue)
 {
 case 0: return QChar(' ');
 case 1: return QChar('\n');
 case 2: return QChar('\r');
 case 3: return QChar('\t');
 case 4: return QChar('`');
 case 5: return QChar('~');
 case 6: return QChar('!');
 case 7: return QChar('@');
 case 8: return QChar('#');
 case 9: return QChar('$');
 case 10: return QChar('%');
 case 11: return QChar('^');
 case 12: return QChar('&');
 case 13: return QChar('*');
 case 14: return QChar('(');
 case 15: return QChar(')');
 case 16: return QChar('=');
 case 17: return QChar('+');
 case 18: return QChar('{');
 case 19: return QChar('}');
 case 20: return QChar('\\');
 case 21: return QChar('|');
 case 22: return QChar(';');
 case 23: return QChar(':');
 case 24: return QChar('\'');
 case 25: return QChar('"');
 case 26: return QChar(',');
 case 27: return QChar('<');
 case 28: return QChar('.');
 case 29: return QChar('>');
 case 30: return QChar('/');
 case 31: return QChar('?');
 default: return QChar(); 
 }
}



QChar Standard_GlyphDeck_8b::get_latex(u1 gp, u1& dia)
{
 Standard_GlyphPack_8b code{gp}; 
 u1 kind, cue;
 std::tie(kind, cue) = code.get_latex_cue();

 switch(kind)
 {
 case 0: return get_text_default(cue);
 case 1: case 3: case 4: dia = cue; return QChar();
 case 2: 
 }
}

QChar Standard_GlyphDeck_8b::get_xml(u1 gp, QString& extra)
{

}

u1 Standard_GlyphDeck_8b::diacritic_code(u1 gp)
{

}


