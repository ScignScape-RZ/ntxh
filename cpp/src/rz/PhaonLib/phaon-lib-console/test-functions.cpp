
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "test-functions.h"


#include <QTextStream>

#include <QDebug>

#include <QEventLoop>

#include "phaon-ir/types/phr-type-system.h"
#include "phaon-ir/phr-code-model.h"
#include "phaon-ir/channel/phr-channel-group.h"
#include "phaon-ir/table/phr-channel-group-table.h"

#include "phaon-ir/channel/phr-channel-system.h"
#include "phaon-ir/channel/phr-carrier.h"
#include "phaon-ir/phaon-ir.h"

USING_KANS(Phaon)

void prn(qint32 arg)
{
 qDebug() << arg;
}

void init_test_functions(PhaonIR& phr, PHR_Code_Model& pcm,
  PHR_Channel_Group_Table& table, PHR_Symbol_Scope& pss)
{
 PHR_Type_System* type_system = pcm.type_system();
 PHR_Channel_System& pcs = *phr.channel_system();


 PHR_Channel_Group g1;
 {
  PHR_Type* ty = type_system->get_type_by_name("u4");
  PHR_Carrier* phc = new PHR_Carrier;
  phc->set_phr_type(ty);
  PHR_Channel_Semantic_Protocol* pcsp = pcs["lambda"];
  g1.init_channel(pcsp, 1);
  (*g1[pcsp])[0] = phc;

  table.init_phaon_function(g1, pss, "prn", 700, &prn);
 }

}

