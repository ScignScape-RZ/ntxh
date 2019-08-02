
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

USING_KANS(Phaon)

extern void default_phr_startup(PhaonIR& phr);


int main(int argc, char* argv[])
{
 PHR_Channel_System pcs;

 PhaonIR phr(&pcs);

 default_phr_startup(phr);

 PHR_Code_Model& pcm = *phr.code_model();

 pcm.set_direct_eval_fn(&phr_direct_eval);
 pcm.create_and_register_type_object("PHR_Fn_Doc*");

//?? PHR_Env* penv = new PHR_Env(&pcm);
 QString penv_typename = "PHR_Env*";
 //??insert_envv(&penv_typename, penv);

 PHR_Runtime_Scope prs(nullptr);

 PHR_Symbol_Scope pss(&prs);

 pcm.create_and_register_type_object("PHR_Env*");

 init_test_functions(phr, pcm, *phr.table(), pss);

 phr.hold_symbol_scope(&pss);

 PHR_Command_Package pcp(&pcs, phr.type_system());
// pcp.parse_from_file( DEFAULT_KPH_FOLDER "/dataset/raw/t1.kph" );
 pcp.parse_from_file( DEFAULT_KPH_FOLDER "/test/raw/t1.kph" );

 //?PHR_Channel_Group pcg(pcp);

 PHR_Runner phrn(phr.code_model());

 KPH_Generator gen (DEFAULT_KPH_FOLDER "/gen/t1.txt");
 phr.code_model()->set_kph_generator(&gen);

 phrn.run(pcp, &pss);

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
