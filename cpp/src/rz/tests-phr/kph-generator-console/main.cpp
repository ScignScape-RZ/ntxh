
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

#include "relae-graph/relae-caon-ptr.h"

#include "phr-env/phr-env.h"
#include "phr-fn-doc/phr-fn-doc.h"

#include "test-functions.h"


#include <QObject>

#include "kans.h"


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
 QString penv_typename = "PHR_Env*";

 PHR_Runtime_Scope prs(nullptr);

 PHR_Symbol_Scope pss(&prs);

 pcm.create_and_register_type_object("PHR_Env*");

 init_test_functions(phr, pcm, *phr.table(), pss);

 phr.hold_symbol_scope(&pss);

 PHR_Command_Package pcp(&pcs, phr.type_system());
 pcp.parse_from_file( DEFAULT_KPH_FOLDER "/test/raw/t1.kph" );
 PHR_Runner phrn(phr.code_model());

 KPH_Generator gen (DEFAULT_KPH_FOLDER "/gen/t1.txt");
 phr.code_model()->set_kph_generator(&gen);

 phrn.run(pcp, &pss);

 return 0;
}

