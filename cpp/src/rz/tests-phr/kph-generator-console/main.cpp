
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "kph-generator/kph-generator.h"

#include "phaon-ir/channel/phr-channel-group.h"

#include "phaon-ir/phr-code-model.h"

#include "phr-direct-eval/phr-direct-eval.h"

#include "phaon-ir/table/phr-symbol-scope.h"

#include "phaon-ir/runtime/phr-command-package.h"

#include "phaon-lib/phr-runner.h"

//#include "phaon-ir/

//#include "kauvir-phaon/kph-command-package.h"
//#include "kauvir-code-model/kauvir-code-model.h"
//#include "kauvir-code-model/kcm-channel-group.h"
//#include "kcm-scopes/kcm-scope-system.h"


//#include "PhaonLib/phaon-namespace.h"
//#include "PhaonLib/phaon-class.h"
//#include "PhaonLib/phaon-function.h"
//#include "PhaonLib/phaon-symbol-scope.h"

#include "relae-graph/relae-caon-ptr.h"

#include "phr-env/phr-env.h"
#include "phr-fn-doc/phr-fn-doc.h"

#include "test-functions.h"

//#include "PhaonLib/phaon-channel-group-table.h"
//#include "PhaonLib/phaon-runner.h"
//#include "kcm-direct-eval/kcm-direct-eval.h"

#include <QObject>

#include "kans.h"


//?USING_KANS(Phaon)


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
 phr.create_channel_semantic_protocol("fground");

 pcm.set_direct_eval_fn(&phr_direct_eval);

// pcm.create_and_register_type_object("PHR_Fn_Doc");
 pcm.create_and_register_type_object("PHR_Fn_Doc*");

//?? PHR_Env* penv = new PHR_Env(&pcm);
 QString penv_typename = "PHR_Env*";

 //??insert_envv(&penv_typename, penv);

 PHR_Runtime_Scope prs(nullptr);

 PHR_Symbol_Scope pss(&prs);

 phr.init_table();

 pcm.create_and_register_type_object("PHR_Env*");

 init_test_functions(phr, pcm, *phr.table(), pss);

// int64_t* n = new int64_t;

 phr.hold_symbol_scope(&pss);

 PHR_Command_Package pcp(&pcs, phr.type_system());
// pcp.parse_from_file( DEFAULT_KPH_FOLDER "/dataset/raw/t1.kph" );
 pcp.parse_from_file( DEFAULT_KPH_FOLDER "/test/raw/t1.kph" );

 PHR_Channel_Group pcg(pcp);

 //int64_t* n1 = new int64_t;

 PHR_Runner phrn(phr.code_model());
 //phrn.init(phr.code_model());

// int64_t* n2 = new int64_t;

 KPH_Generator gen (DEFAULT_KPH_FOLDER "/gen/t1.txt");
 phr.code_model()->set_kph_generator(&gen);

 phrn.run(pcg, &pss);

 return 0;
}

int main1(int argc, char* argv[])
{
 KPH_Generator gen (DEFAULT_KPH_FOLDER "/gen/t1.txt");


// Phaon_Runner phr;

// Phaon_Namespace phn("TestNS");
// Phaon_Class phc("Test_Class", &phn);

// Kauvir_Code_Model& kcm = phr.get_kcm();
// kcm.set_kph_generator(&gen);
// kcm.set_direct_eval_fn(&kcm_direct_eval);
// Phaon_Symbol_Scope pss;
// init_test_functions(kcm, phr.get_table(), pss);
// phr.get_phaon_scope_queue().push_front(&pss);

// PHR_Command_Package pcp;
// pcp.parse_from_file( DEFAULT_KPH_FOLDER "/dataset/raw/t1.kph" );

 //PHR_Channel_Group pcg(kcm.channel_names());
 //khp.init_channel_group(kcm, kcg);
 //phr.run(kcg);

 return 0;
}
