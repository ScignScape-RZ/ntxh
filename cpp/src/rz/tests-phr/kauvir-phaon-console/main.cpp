
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phaon-ir/runtime/phr-command-package.h"

#include "phaon-ir/table/phr-symbol-scope.h"

#include "phr-env/phr-env.h"
#include "phr-fn-doc/phr-fn-doc.h"

//#include "kauvir-code-model/kauvir-code-model.h"
//#include "kauvir-code-model/kcm-channel-group.h"
//#include "kcm-scopes/kcm-scope-system.h"

//#include "PhaonLib/phaon-namespace.h"
//#include "PhaonLib/phaon-class.h"
//#include "PhaonLib/phaon-function.h"
//#include "PhaonLib/phaon-symbol-scope.h"

#include "relae-graph/relae-caon-ptr.h"

#include "test-functions.h"

//#include "PhaonLib/phaon-channel-group-table.h"
//#include "PhaonLib/phaon-runner.h"

//
#include "phr-direct-eval/phr-direct-eval.h"

//#include "kcm-command-package/kcm-command-package.h"

#include "phaon-lib/phr-runner.h"

#include "phaon-ir/phr-code-model.h"
#include "phaon-ir/scopes/phr-scope-system.h"


#include "kans.h"

//USING_KANS(KCM)
//USING_KANS(Phaon)
//USING_KANS(PhaonLib)

#include "phaon-ir/phaon-ir.h"
#include "phaon-ir/channel/phr-channel-system.h"


int main(int argc, char* argv[])
{
// PHR_Runner phr;
//// Phaon_Namespace phn("TestNS");
//// Phaon_Class phc("Test_Class", &phn);
// PHR_Code_Model& pcm = phr.get_pcm();
// pcm.set_direct_eval_fn(&phr_direct_eval);

 PHR_Channel_System pcs;

 PhaonIR phr(&pcs);

 PHR_Runtime_Scope prs(nullptr);

 PHR_Symbol_Scope pss(&prs);

 phr.init_table();

// PHR_Runner phrn;
// phrn.


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

// pcm.create_and_register_type_object("PHR_Fn_Doc");
 pcm.create_and_register_type_object("PHR_Fn_Doc*");

 PHR_Env* penv = new PHR_Env(&pcm);
 QString penv_typename = "PHR_Env*";
 //??insert_envv(&penv_typename, penv);

 pcm.create_and_register_type_object("PHR_Env*");


 init_test_functions(phr, pcm, *phr.table(), pss);

 phr.hold_symbol_scope(&pss);


// PhaonIR& phr, PHR_Code_Model& pcm,
//   PHR_Channel_Group_Table& table, PHR_Symbol_Scope& pss

// PHR_Symbol_Scope pss(nullptr);
// init_test_functions(phr, pcm, phr.get_table(), pss);

//? phr.get_phaon_scope_queue().push_front(&pss);

 PHR_Command_Package pcp;
 pcp.parse_from_file( DEFAULT_KPH_FOLDER "/test/raw/t1.kph" );

 QByteArray qba;
 pcp.supply_data(qba);

 PHR_Command_Package pcp1;
 pcp1.absorb_data(qba);


 PHR_Channel_Group pcg;//(cm.channel_names());

//?
// pcp1.init_channel_group(pcm, pcg);
// phr.run(pcg);

 return 0;

}
