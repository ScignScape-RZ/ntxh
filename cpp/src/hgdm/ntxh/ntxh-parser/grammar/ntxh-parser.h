
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef NTXH_PARSER__H
#define NTXH_PARSER__H

#include "relae-graph/relae-parser.h"

#include "ntxh/kernel/ntxh-dominion.h"

#include "kans.h"
KANS_(HGDMCore)

//USING_RZNS(RECore)

class NTXH_Graph;

class NTXH_Parser : public Relae_Parser<NTXH_Galaxy>
{
 QString raw_text_;

public:

// // ACCESSORS(NTXH_Graph* ,graph)
 ACCESSORS(QString ,raw_text)

 //ACCESSORS(NTXH_Graph* ,graph)

 NTXH_Parser(caon_ptr<NTXH_Graph> g);

// QString get_remainder();


};

_KANS(HGDMCore)

//#include "rz-parser/rz-regex.h"
//#include "rz-parser/rz-parser.h"

//#include "rz-text-typedefs.h"

//class RZ_Text_Parser : public RZ_Parser<RZ_Text_Galaxy>
//{
//public:
// RZ_Text_Parser(RZ_Text_Graph* g);
// void set_raw_text(QString s);


//};

//typedef RZ_Parser<RZ_Text_Galaxy> RZ_Text_Parser;

#endif
