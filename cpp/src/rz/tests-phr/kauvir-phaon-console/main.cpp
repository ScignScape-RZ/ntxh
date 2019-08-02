
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phaon-ir/runtime/phr-command-package.h"

#include "phaon-ir/table/phr-symbol-scope.h"

#include "phr-env/phr-env.h"
#include "phr-fn-doc/phr-fn-doc.h"


#include "relae-graph/relae-caon-ptr.h"

#include "test-functions.h"

#include "phr-direct-eval/phr-direct-eval.h"

#include "phaon-lib/phr-runner.h"

#include "phaon-ir/phr-code-model.h"
#include "phaon-ir/scopes/phr-scope-system.h"


#include "kans.h"

#include "phaon-ir/phaon-ir.h"
#include "phaon-ir/channel/phr-channel-system.h"

USING_KANS(Phaon)


int main(int argc, char* argv[])
{
 PHR_Channel_System pcs;

 PhaonIR phr(&pcs);

 phr.init_type_system();
 phr.init_type("fbase", DEFAULT_PTR_BYTE_CODE);
 phr.init_type("u4", 4);
 phr.init_type("u8", 8);
 phr.init_type("argvec", 9);
 phr.init_type("pcv", DEFAULT_PTR_BYTE_CODE);
 phr.init_type("str", DEFAULT_PTR_BYTE_CODE);

 qRegisterMetaType<PHR_Fn_Doc>();
 qRegisterMetaType<PHR_Fn_Doc*>();

 // //  setup
 phr.init_code_model();

 PHR_Code_Model& pcm = *phr.code_model();
 pcm.set_type_system(phr.type_system());

 phr.create_channel_semantic_protocol("lambda");
 phr.create_channel_semantic_protocol("result");
 phr.create_channel_semantic_protocol("sigma");

 pcm.set_direct_eval_fn(&phr_direct_eval);

 pcm.create_and_register_type_object("PHR_Fn_Doc*");

 QString penv_typename = "PHR_Env*";

 PHR_Runtime_Scope prs(nullptr);

 PHR_Symbol_Scope pss(&prs);

 phr.init_table();

 pcm.create_and_register_type_object("PHR_Env*");


 init_test_functions(phr, pcm, *phr.table(), pss);

 phr.hold_symbol_scope(&pss);
 PHR_Command_Package pcp(&pcs, phr.type_system());
 pcp.parse_from_file( DEFAULT_KPH_FOLDER "/test/raw/t1.kph" );

 QByteArray qba;
 pcp.supply_data(qba);

 PHR_Command_Package pcp1(&pcs, phr.type_system());
 pcp1.absorb_data(qba);


 PHR_Channel_Group& pcg = pcp1;

 return 0;

}
