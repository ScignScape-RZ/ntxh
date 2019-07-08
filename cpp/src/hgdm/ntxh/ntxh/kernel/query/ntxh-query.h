
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef NTXH_QUERY__H
#define NTXH_QUERY__H

#include "kernel/ntxh-dominion.h"

#include "relae-graph/relae-node-ptr.h"

#include "kans.h"

KANS_(HGDMCore)

//class SY_Connector
//{
// //public:
// QString label_;

// public:
//  SY_Connector(QString label) : label_(label){}

//};

//template<type

class NTXH_Query : public node_query<NTXH_Dominion>
{
 NTXH_Query();
 // SY_Dominion::Connectors N_A;
 public:
  #define DOMINION_CONNECTOR(name, label) \
   NTXH_Connectors name;
  #include "kernel/dominion/connectors.h"
  #undef DOMINION_CONNECTOR

 static const NTXH_Query& instance();
};

_KANS(HGDMCore)

#endif
