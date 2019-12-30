
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "standard-glyphdeck-8b.h"

#include "standard-glyphpack-8b.h"

#include "glyph-argument-package.h"


USING_KANS(HTXN)

Standard_GlyphDeck_8b::Standard_GlyphDeck_8b()
 :  deck_id_(0)
{

}

//void Standard_GlyphDeck_8b::check_external_excluding_numeral_diacritic
//  (u1 gp, Glyph_Argument_Package& gap)
//{
// if( (gp > 63) && (gp < 74) )
//   gap.glyph_code = (u8) gp;
// else if(gp == 100)
//   gap.glyph_code = (u8) gp;
// else
//   check_external(gp, gap);
//}

void Standard_GlyphDeck_8b::get_htxne_out(u1 gp, Glyph_Argument_Package& gap)
{
 if(gp < 64)
 {
  gap.chr = get_text_default(gp);
  return;
 }
 gap.chr = get_nondiacritic_default(gp & 63);
 
 // //  get alt number 
 static QMap<u1, u1> static_map {
  { Standard_GlyphDeck_8b::NpDot, 1 },
  { Standard_GlyphDeck_8b::NsPer, 2 },
  { Standard_GlyphDeck_8b::NpExcX, 1 },
  { Standard_GlyphDeck_8b::NpOParX, 1 },
  { Standard_GlyphDeck_8b::NpCParX, 1 },
  { Standard_GlyphDeck_8b::DashSML, 1 },
  { Standard_GlyphDeck_8b::NpMinus, 2 },
  { Standard_GlyphDeck_8b::DashX, 3 },
  { Standard_GlyphDeck_8b::SnDash, 4 },
  { Standard_GlyphDeck_8b::NpMinus, 2 },
  { Standard_GlyphDeck_8b::SnDash, 4 },

  { Standard_GlyphDeck_8b::NmComX, 1 },
  { Standard_GlyphDeck_8b::SqSqX, 1 },
  { Standard_GlyphDeck_8b::TxtNumX, 1 },
  { Standard_GlyphDeck_8b::TxtDolX, 1 },
  { Standard_GlyphDeck_8b::TxtPerX, 1 },
  { Standard_GlyphDeck_8b::TxtAmpX, 1 },
  { Standard_GlyphDeck_8b::SqDqX, 1 },
  { Standard_GlyphDeck_8b::TxtStarX, 1 },
  { Standard_GlyphDeck_8b::TxtPlusX, 1 },
  { Standard_GlyphDeck_8b::FslX, 1 },

  { Standard_GlyphDeck_8b::NpColX, 1 },
  { Standard_GlyphDeck_8b::NpSemX, 1 },
  { Standard_GlyphDeck_8b::NpQmX, 1 },
  { Standard_GlyphDeck_8b::IndQm, 1 },
  { Standard_GlyphDeck_8b::NpLtX, 1 },
  { Standard_GlyphDeck_8b::NpGtX, 1 },
  { Standard_GlyphDeck_8b::OSqBrX, 1 },
  { Standard_GlyphDeck_8b::CSqBrX, 1 },
  { Standard_GlyphDeck_8b::OCyBrX, 1 },
  { Standard_GlyphDeck_8b::CCyBrX, 1 },
  { Standard_GlyphDeck_8b::BslX, 1 },
  { Standard_GlyphDeck_8b::NullX, 1 },
 };

 u1 alt_code = static_map.value(gap.glyph_code);
 switch(alt_code)
 {
 default: // // should always be 0 - 4 ...
 case 0:
  break;
 case 1:
  {
   gap.flags.has_alt = true;
   gap.flags.alt_1 = true; break;
  }
 case 2:
  {
   gap.flags.has_alt = true;
   gap.flags.alt_2 = true; break;
  }
 case 3:
  {
   gap.flags.has_alt = true;
   gap.flags.alt_3 = true; break;
  }
 case 4:
  {
   gap.flags.has_alt = true;
   gap.flags.alt_4 = true; break;
  }
 }

} 

void Standard_GlyphDeck_8b::check_external(u1 gp, Glyph_Argument_Package& gap)
{
 if( (gp > 63) && (gp < 74) && (!gap.interpret.flags.use_numeral_diacritic) )
 {
  gap.flags.normal = true;
  return;
 }
 if( (gp == 100) && (!gap.interpret.flags.use_underscore_diacritic) )
 {
  gap.flags.normal = true;
  return;
 }
 if( (gp > 100) && (gp < 123) && gap.interpret.flags.use_refinements )
 {
  gap.flags.maybe_refinement = true;
 }
 if( (gp & 128) > 0 )
 {
  gap.flags.maybe_external_deck = true;
  // // provisional; may revert to gp ...
  gap.glyph_code = (u8) gp & 127;   
  return;
 }
 if( (gp & 64) > 0 )
 {
  gap.flags.maybe_external_diacritic = true;
  // // provisional; may revert to gp ...
  gap.glyph_code = (u8) gp & 63;
  return;
 }
 gap.flags.normal = true;
}

void Standard_GlyphDeck_8b::get_qstring_out(u1 gp, Glyph_Argument_Package& gap)
{
 if(gp < 64)
   gap.chr = get_text_default(gp);
 else
   gap.chr = get_nondiacritic_default(gp - 64);
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
 case 36: return QChar('_');
 case 37: return QChar('A');
 case 38: return QChar('B');
 case 39: return QChar('C');
 case 40: return QChar('D');
 case 41: return QChar('E');
 case 42: return QChar('F');
 case 43: return QChar('G');
 case 44: return QChar('H');
 case 45: return QChar('I');
 case 46: return QChar('J');
 case 47: return QChar('K');
 case 48: return QChar('L');
 case 49: return QChar('M');
 case 50: return QChar('N');
 case 51: return QChar('O');
 case 52: return QChar('P');
 case 53: return QChar('Q');
 case 54: return QChar('R');
 case 55: return QChar('S');
 case 56: return QChar('T');
 case 57: return QChar('U');
 case 58: return QChar('V');
 case 59: return QChar('W');
 case 60: return QChar('X');
 case 61: return QChar('Y');
 case 62: return QChar('Z');
 case 63: return QChar(' ');
 default: return QChar(); 
 }
}

#ifdef HIDE
QString Standard_GlyphDeck_8b::get_nondiacritic_xdefault_latex(u1 cue)
{
 switch(cue)
 {
 case 0: return QString();
 case 1: return QString();
 case 2: return QString("{\\DLi}");
 case 3: return QString("{\\DLj}");
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
#endif //def HIDE

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
 case 0: return QChar('.'); // // 64
 case 1: return QChar('!'); // // 65
 case 2: return QChar('('); // // 66
 case 3: return QChar(')'); // // 67
 case 4: return QChar('-'); // // 68  // hyphen
 case 5: return QChar(','); // // 69
 case 6: return QChar('\''); // // 70
 case 7: return QChar(':'); // // 71
 case 8: return QChar(';'); // // 72
 case 9: return QChar('?'); // // 73

 case 10: return QChar('-'); // // 74  // NpMinus
 case 11: return QChar('+'); // // 75

 case 12: return QChar('.'); // // 76  // NpDot
 case 13: return QChar('#'); // // 77
 case 14: return QChar('$'); // // 78
 case 15: return QChar('%'); // // 79
 case 16: return QChar('&'); // // 80
 case 17: return QChar('-'); // // 81 // SnDash
 case 18: return QChar('-'); // // 82 // DashSML
 case 19: return QChar('='); // // 83

 case 20: return QChar('['); // // 84
 case 21: return QChar(']'); // // 85

 case 22: return QChar('/'); // // 86

 case 23: return QChar('?'); // // 87  // IndQm
 case 24: return QChar('.'); // // 88  // NsPer
 case 25: return QChar('?'); // // 89  // NsQm
 case 26: return QChar('!'); // // 90  // NsExc
 case 27: return QChar(' '); // // 91  // SnSp

 case 28: return QChar('\n'); // // 92 // Boundary

 case 29: return QChar('\t'); // // SpaceX

 case 30: return QChar('-'); // // 89 // DashX
 case 31: return QChar('/'); // // 90  // FslX

 case 32: return QChar('['); // // 91  // OSqBrX
 case 33: return QChar(']'); // // 92  // CSqBrX


 case 34: return QChar('{'); // // 93  // OCyBrX
 case 35: return QChar('}'); // // 94  // CCyBrX

 case 36: return QChar('\n'); // // 95  // Null

 case 37: return QChar('^'); // // 100  // TxtHatX
 case 38: return QChar(','); // // 101  // NpCmaX
 case 39: return QChar('\''); // // 102  // SqSqX
 case 40: return QChar(':'); // // 103  // NpColX
 case 41: return QChar(';'); // // 104  // NpSemX
 case 42: return QChar('?'); // // 105  // NpQmX

 case 43: return QChar('\\'); // // 106  // BslX
 case 44: return QChar('|'); // // 107  // PipeX 

 case 45: return QChar('#'); // // 109  // TxtNumX
 case 46: return QChar('$'); // // 110  // TxtDolX
 case 47: return QChar('%'); // // 111  // TxtPerX
 case 48: return QChar('+'); // // 112  // TxtPlusX
 case 49: return QChar('&'); // // 113  // TxtAmpX

 case 50: return QChar('*'); // // 114  // TxtStarX
 case 51: return QChar('='); // // 115  // TxtEqX

 case 52: return QChar('!'); // // 116  // NpExcX
 case 53: return QChar('('); // // 117  // NpOParX
 case 54: return QChar(')'); // // 118  // NpCParX

 case 55: return QChar('.'); // // 119  // NmDotX
 case 56: return QChar('<'); // // 120  // NpLtX
 case 57: return QChar('>'); // // 121  // NpGtX
 case 58: return QChar(','); // // 122  // NmComX
 case 59: return QChar('"'); // // 123  // SqDqX

 case 60: return QChar('@'); // // 124  // TxtAtX
 case 61: return QChar('`'); // // 125  // BqX
 case 62: return QChar('~'); // // 126  // TildeX
 case 63: return QChar('\n'); // // 127

 default: return QChar(); 
 }
}

void Standard_GlyphDeck_8b::get_nondiacritic_supplement(u1 cue, QString& result)
{
 static QVector<QString> static_vec {
  "", //0: return QChar('.'); // // 65
  "", //1: return QChar('!'); // // 65
  "", //2: return QChar('('); // // 66
  "", //3: return QChar(')'); // // 67
  "", //4: return QChar(','); // // 68
  "", //5: return QChar('~'); // // 69
  "", //6: return QChar('\''); // // 70
  "", //7: return QChar(':'); // // 71
  "", //8: return QChar(';'); // // 72
  "", //9: return QChar('?'); // // 73
  "", //10: return QChar('-'); // // 74

  "", //11: return QChar('+'); // // 75
  "", //12: return QChar('@'); // // 76
  "", //13: return QChar('#'); // // 77
  "", //14: return QChar('$'); // // 78
  "", //15: return QChar('%'); // // 79
  "", //16: return QChar('^'); // // 80
  "", //17: return QChar('&'); // // 81
  "", //18: return QChar('*'); // // 82
  "", //19: return QChar('='); // // 83

  "", //20: return QChar('{'); // // 84
  "", //21: return QChar('}'); // // 85
  "", //22: return QChar('['); // // 86
  "", //23: return QChar(']'); // // 87
  "", //24: return QChar('<'); // // 88
  "", //25: return QChar('>'); // // 89
  "", //26: return QChar('\\'); // // 90
  "", //27: return QChar('/'); // // 91
  "", //28: return QChar('|'); // // 92
  "", //29: return QChar('"'); // // 93
  "", //30: return QChar('~'); // // 94
  "", //31: return QChar('`'); // // 95
 };
 
}


void Standard_GlyphDeck_8b::get_latex(u1 gp, Glyph_Argument_Package& gap)
{
 Standard_GlyphPack_8b code{gp}; 
 u1 kind, cue;
 std::tie(kind, cue) = code.get_latex_cue();

 switch(kind)
 {
// case 0: return get_text_default(cue);
// case 1: case 3: case 4: dia = cue; return QChar();
// case 2:
 }
}


void Standard_GlyphDeck_8b::get_latex_dia(u1 gp, Glyph_Argument_Package &gap)
{

}

void Standard_GlyphDeck_8b::get_xml(u1 gp, Glyph_Argument_Package& gap)
{

}

void Standard_GlyphDeck_8b::get_xml_dia(u1 gp, Glyph_Argument_Package& gap)
{

}


