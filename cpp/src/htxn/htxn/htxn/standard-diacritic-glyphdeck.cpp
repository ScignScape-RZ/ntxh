
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "standard-diacritic-glyphdeck.h"

void Standard_Diacritic_GlyphDeck::get_qstring_out
  (u2 code, u1 gp, char cue, QString& result)
{
 static QMap<u2, QString> static_map {
 };
 result = static_map.value(code, cue);
}

void Standard_Diacritic_GlyphDeck::get_latex_out
  (u2 code, u1 gp, u1 scope, char cue, QString& result)
{
 if(gp == 0)
 {
  result = "{\\IndQM}";
  return;
 }
 static QMap<u2, QString> static_map {
  { 
//   { 10136, "{\\/}" }, // _._
 
   { 12123, "{\\ng}" },  //  g.n
   { 12150, "{\\NG}" },  //  g.N

   { 12110, "{\\&}" },  //  g.a
   { 12120, "\\textsc{k}" },  //  g.k
   { 12147, "{\\Kgreenalt}" },  //  g.K  
  
   { 12223, "{\\ngalt}" },  //  G.n  
   { 12250, "{\\NGalt}" },  //  G.N 
 
   { 12210, "{\\itampalt}" },  //  G.a  
   { 12120, "{\\kGreenalt}" },  //  G.k
   { 12147, "{\\Kgreenalt}" },  //  G.K  

   { 11610, "{\\aa}" },  //  R.a  
   { 11637, "{\\AA}" },  //  R.a  

   { 12310, "{\\dh}" },  //  h.d  
   { 12337, "{\\DH}" },  //  h.D  
   { 12329, "{\\th}" },  //  h.t  
   { 12356, "{\\TH}" },  //  h.T  

   { 12428, "{\\ss}" },  //  z.s  
   { 12455, "{\\sSalt}" },  //  z.S  

   { 12510, "{\\ae}" },  //  e.a  
   { 12524, "{\\oe}" },  //  e.o  
   { 12537, "{\\Aealt}" },  //  e.A
   { 12551, "{\\Oealt}" },  //  e.O
  
   { 12610, "{\\aEalt}" },  //  E.a  
   { 12624, "{\\oEalt}" },  //  E.o  
   { 12637, "{\\AE}" },  //  E.A  
   { 12651, "{\\OE}" },  //  E.O 

   { 13136, "{\\/}" }, // C._

   { 13212, "{\\textcopyright}" }, // @.c
   { 13227, "{\\textregistered}" }, // @.r

   { 13412, "{\\textcopyleft}" }, // %.c

   { 13936, "{\\\"}"}" }, // D._

   { 13227, "{\\textregistered}" }, // @.r
   { 13412, "{\\textcopyleft}" }, // %.c

   { 14629, "{\\texttrademark}" }, // :.t
   { 24629, "{\\ttrademark" }, // :.t

   { 14631, "{\\textservicemark}" }, // :.v
   { 24631, "{\\tservicemark" }, // :.v

   { 14628, "{\\diaST}" }, // :.s  i.e. 1st ...
   { 24628, "{\\ddiaST}" }, // :.s
   { 14655, "{\\altdiaST}" }, // :.S  
   { 24655, "{\\altddiaST" }, // :.S

   { 14623, "{\\diaND}" }, // :.n  i.e. 2nd ...
   { 24623, "{\\ddiaND}" }, // :.n
   { 14650, "{\\altdiaND}" }, // :.N  
   { 24650, "{\\altddiaND" }, // :.N

   { 14627, "{\\diaND}" }, // :.r  i.e. 3rd ...
   { 24627, "{\\ddiaND}" }, // :.r
   { 14654, "{\\altdiaND}" }, // :.R  
   { 24654, "{\\altddiaND" }, // :.R

   { 14617, "{\\diaND}" }, // :.h  i.e. 4th ...
   { 24617, "{\\ddiaND}" }, // :.h
   { 14644, "{\\altdiaND}" }, // :.H  
   { 24644, "{\\altddiaND" }, // :.H

  } 
 };
 auto it = static_map.find(code);
 if(it == static_map.end())
 {
  QChar rep;
  get_representation(gp, rep);
  if( cue == '_' )
    result = QString("\\%1{}").arg(rep);
  else if( ((cue == 'i') || (cue == 'j')) 
    && (gp != 14) ) // ogon
  {
   if(gp == 1) // _.i or _.j
     result = QString("{\\%2nodot}").arg(rep).arg(cue);
   else    
     result = QString("\\%1{\\%2nodot}").arg(rep).arg(cue);
  }
  else if(gp < 16) //  normal ...
    result = QString("\\%1{%2}").arg(rep).arg(cue);
  else 
  {
   switch(gp)
   {
   case 17: // K
    result = QString("{\\%2strok}").arg(rep); break;      
   case 20: // m
    result = QString("{\\%2midot}").arg(rep); break;      
   case 18: // t
    result = QString("{\\%2midot}").arg(rep); break;      
   case 19: // t
    if(scope == 1)
      result = QString("\\t{%1}").arg(rep); 
    else
      result = QString("\\t{%1").arg(rep);   
    break; 
   case 20: // t
    if( (cue == 'o') || (cue == 'O' )
      result = QString("{\\%1").arg(QChar::fromLatin1(cue)); 
    else
      result = QString("\\%1slash").arg(rep);   
    break;          
   case 27: // f
    if(scope == 1)
      result = QString("\\fLig{%1}").arg(rep); 
    else if(scope == 2)
      result = QString("\\fLigg{%1").arg(rep); 
    else if(scope == 3)
      result = QString("\\fLiggg{%1").arg(rep); 
    break; 
   case 28: // F
    if(scope == 1)
      result = QString("\\ffLig{%1}").arg(rep); 
    else if(scope == 2)
      result = QString("\\ffLigg{%1").arg(rep); 
    else if(scope == 3)
      result = QString("\\ffLiggg{%1").arg(rep); 
    break;
   case 29: // n
    if(scope == 1)
      result = QString("\\noLig{%1}").arg(rep); 
    else if(scope == 2)
      result = QString("\\noLigg{%1").arg(rep); 
    else if(scope == 3)
      result = QString("\\noLiggg{%1").arg(rep); 
    break;
   case 30: // N
    if(scope == 1)
      result = QString("\\NoLig{%1}").arg(rep); 
    else if(scope == 2)
      result = QString("\\NoLigg{%1").arg(rep); 
    else if(scope == 3)
      result = QString("\\NoLiggg{%1").arg(rep); 
    break;
   case 31: // C
    if(scope == 1)
      result = QString("\\AltNoLig{%1}").arg(rep); 
    else if(scope == 2)
      result = QString("\\AltNoLigg{%1").arg(rep); 
    else if(scope == 3)
      result = QString("\\AltNoLiggg{%1").arg(rep); 
    break;
   case 33: // circled
    if(scope == 1)
      result = QString("\\diacircled{%1}").arg(rep);
    else
      result = QString("\\diacircled{%1").arg(rep);
    break;
   case 34: // circled flip
    if(scope == 1)
      result = QString("\\diacircledflip{%1}").arg(rep);
    else
      result = QString("\\diacircledflip{%1").arg(rep);
    break;
   case 35: // circle ring
    result = QString("\\diacirclering{%1}").arg(rep);
    break;
   case 36: // circle Ring
    result = QString("\\diacircleRing{%1}").arg(rep);
    break;
   case 37: // $
    result = QString("\\diavstrike{%1}").arg(rep);
    break;
   case 38: // -
    result = QString("\\diahstrike{%1}").arg(rep);
    break;
   case 39: // D
    result = QString("\\\"{%1}").arg(rep);
    break;

   case 46: // :
    if(scope == 1)
      result = QString("\\diaele{%1}").arg(rep);
    else
      result = QString("\\diaele{%1").arg(rep);
    break;

   case 47: // inherited
    result = QString("%1}").arg(rep);
    break;

   case 48: // middle inherited
    result = rep;
    break;

   case 49: // double inherited
    result = QString("%1}").arg(rep);
    break;

   case 62: // V
    result = QString("\\diainv{%1}").arg(rep);
    break;

   case 63: // ?
    result = QString("\\diaNotRecognized{%1}").arg(rep);
    break;

   default:     
    result = QString("\\%1{%2}").arg(rep).arg(cue); break; 
   }
  }
 }
}

QString Standard_Diacritic_GlyphDeck::get_latex_out(u1 gp, char cue)
{
 QString result;
 u1 scope = (gp >> 6) + 1;
 u1 code = gp;
 code &= 63;
 code *= 100;
 code += (scope * 10000);
 code += get_cue_code(cue);
 get_latex_out(code, gp, scope, cue, result);
 return result;
}

QString Standard_Diacritic_GlyphDeck::get_qstring_out(u1 gp, char cue)
{
 QString result;
 u1 scope = (gp >> 6) + 4;
 u1 code = gp;
 code &= 63;
 code *= 100;
 code += (scope * 10000);
 code += get_cue_code(cue);
 get_qstring_out(code, gp, cue, result);
 return result;
}

u1 Standard_Diacritic_GlyphDeck::get_cue_code(char cue)
{
 switch(cue)
 {
 case '0': return 0;
 case '1': return 1;
 case '2': return 2;
 case '3': return 3;
 case '4': return 4;
 case '5': return 5;
 case '6': return 6;
 case '7': return 7;
 case '8': return 8;
 case '9': return 9;

 case 'a': return 10;
 case 'b': return 11;
 case 'c': return 12;
 case 'd': return 13;
 case 'e': return 14;
 case 'f': return 15;
 case 'g': return 16;
 case 'h': return 17;
 case 'i': return 18;
 case 'j': return 19;
 case 'k': return 20;
 case 'l': return 21;
 case 'm': return 22;
 case 'n': return 23;
 case 'o': return 24;
 case 'p': return 25;
 case 'q': return 26;
 case 'r': return 27;
 case 's': return 28;
 case 't': return 29;
 case 'u': return 30;
 case 'v': return 31;
 case 'w': return 32;
 case 'x': return 33;
 case 'y': return 34;
 case 'z': return 35;

 case '_': return 36;

 case 'A': return 37;
 case 'B': return 38;
 case 'C': return 39;
 case 'D': return 40;
 case 'E': return 41;
 case 'F': return 42;
 case 'G': return 43;
 case 'H': return 44;
 case 'I': return 45;
 case 'J': return 46;
 case 'K': return 47;
 case 'L': return 48;
 case 'M': return 49;
 case 'N': return 50;
 case 'O': return 51;
 case 'P': return 52;
 case 'Q': return 53;
 case 'R': return 54;
 case 'S': return 55;
 case 'T': return 56;
 case 'U': return 57;
 case 'V': return 58;
 case 'W': return 59;
 case 'X': return 60;
 case 'Y': return 61;
 case 'Z': return 62;
 default: break;
 }

}

void get_qstring_out(u2 code); 


u1 Standard_Diacritic_GlyphDeck::get_code(char cue, u1 scope)
{
 u1 result = 0;
 switch(cue)
 {
 case '_': result = 1; break;
 case '`': result = 2; break;
 case '\'': result = 3; break;
 case '^': result = 4; break;
 case '"': result = 5; break;
 case '~': result = 6; break;
 case '=': result = 7; break;
 case '.': result = 8; break;
 case 'u': result = 9; break;

 case 'v': result = 10; break;
 case 'H': result = 11; break;
 case 'b': result = 12; break;
 case 'c': result = 13; break;
 case 'k': result = 14; break;
 case 'r': result = 15; break;
 case 'R': result = 16; break;
 case 'K': result = 17; break;
 case 't': result = 18; break;

 case '/': result = 19; break;
 case 'm': result = 20; break;
 case 'g': result = 21; break;
 case 'G': result = 22; break;
 case 'h': result = 23; break;
 case 'z': result = 24; break;
 case 'e': result = 25; break;
 case 'E': result = 26; break;
 case 'f': result = 27; break;

 case 'F': result = 28; break;
 case 'n': result = 29; break;
 case 'N': result = 30; break;
 case 'C': result = 31; break;
 case '@': result = 32; break;
 case ')': result = 33; break;
 case '%': result = 34; break;
 case 'o': result = 35; break;
 case 'O': result = 36; break;

 case '$': result = 37; break;
 case '-': result = 38; break;
 case 'D': result = 39; break;
 case '[': result = 40; break;
 case ']': result = 41; break;
 case '{': result = 42; break;
 case '}': result = 43; break;
 case ',': result = 44; break;
 case ';': result = 45; break;

 case ':': result = 46; break;
 case '<': result = 47; break;
 case '+': result = 48; break;
 case '>': result = 49; break;
 case '0': result = 50; break;
 case '1': result = 51; break;
 case '2': result = 52; break;
 case '3': result = 53; break;
 case '4': result = 54; break;

 case '5': result = 55; break;
 case '6': result = 56; break;
 case '7': result = 57; break;
 case '8': result = 58; break;
 case '9': result = 59; break;
 case '#': result = 60; break;
 case '*': result = 61; break;
 case 'V': result = 62; break;
 case '?': result = 63; break;
 default: break;
 }

 switch(scope)
 {
 default:
 case 1: return result;
 case 2: return result + 64;
 case 3: return result + 128;
 case 4: return result + 192;
 }
}

#ifdef HIDE
0: null
1: _ empty
2: ` // acute
3: ' // grave
4: ^ // circ
5: " // uml
6: ~ // tilde
7: = // macr
8: . // dot
9: u // breve
10: v // caron
11: H // dbl acute
12: t // tie-after 
13: c // cedil
14: r // ring over ...
15: R // ring over (alt), e.g. aa instead of ra ...
16: k // ogon
17: b // bar-under
18: K // stroke
19: / // slash
20: m // midot
21: g // eng, kgreen, |&  ...
22: G // eng, |& with more space

23: h // eth, thorn, Thorn 
24: z // eszat i.e. ss ...

25: e // ae, oe
26: E // AE, OE

27: f // fi, fj, fl, ff, FI, FJ, FL, FF 

28: F // fi, ffj, ffl, FFI, FFJ, FFL

29: n // no ligature
30: N // no ligature
31: C // italic correction

32: ) // circled left
33: @ // special circled

34: ( // circled

35: $ // strike
36: - // strike

37: # // special 
38: % // special 
39: * // special

40: [
41: ]
42: {
43: }
44: ,
45: ;

46: : // elevated

// // multi-character codes: 
 //    + double elevated
 //    > double 
 //    & triple
 //    \ external 
 //   e.g.
 //     |:t (TM as one character)   
 //     |+t (TM as two characters) 
 //     |fl (fl ligature as one character)
 //     |Fl (ffl ligature as one character)
 //     |>fl (fl ligature as two character)
 //     |&Fl (ffl ligature as three characters) 


47: < // inherited
48: + // middle inherited
49: > // double inherited



50: 0
51: 1
52: 2
53: 3
54: 4
55: 5
56: 6
57: 7
58: 8
59: 9

60: D // dieresis
61: i // generic italics  

62: V (invert)

63: ? // unrec

#endif //def HIDE


