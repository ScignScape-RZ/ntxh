
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
 case 2: return QString("{\DLi}");
 case 3: return QString("{\DLj});
 case 4: return QString("a");
 case 5: return QString("b");
 case 6: return QString("c");
 case 7: return QString("d");
 case 8: return QString("e");
 case 9: return QString("f");
 case 10: return QString("g");
 case 11: return QString("h");
 case 12: return QString("i");
 case 13: return QString("j");
 case 14: return QString("k");
 case 15: return QString("l");
 case 16: return QString("m");
 case 17: return QString("n");
 case 18: return QString("o");
 case 19: return QString("p");
 case 20: return QString("q");
 case 21: return QString("r");
 case 22: return QString("s");
 case 23: return QString("t");
 case 24: return QString("u");
 case 25: return QString("v");
 case 26: return QString("w");
 case 27: return QString("x");
 case 28: return QString("y");
 case 29: return QString("z");
 case 30: return QString("/");
 case 31: return QString("?");
 default: return QChar(); 
}

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



QChar Standard_GlyphDeck_8b::get_latex(u1 gp, QString& extra)
{
 Standard_GlyphPack_8b code{gp}; 
 u1 cue = code.get_latex_cue();
 return get_text_default(cue);
}

QChar Standard_GlyphDeck_8b::get_xml(u1 gp, QString& extra)
{

}

u1 Standard_GlyphDeck_8b::diacritic_code(u1 gp)
{

}


