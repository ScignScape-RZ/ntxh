
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "phaon-lib/phr-runner.h"

#include "phaon-ir/phaon-ir.h"
#include "phaon-ir/channel/phr-channel-system.h"

#include "phaon-ir/phr-code-model.h"

#include "phaon-ir/table/phr-symbol-scope.h"

#include "phaon-ir/scopes/phr-runtime-scope.h"

#include "phr-direct-eval/phr-direct-eval.h"

#include "test-functions.h"

USING_KANS(Phaon)


void local_program(PhaonIR& phr)
{
 phr.init_type_system();
 phr.init_type("fbase", DEFAULT_PTR_BYTE_CODE);
 phr.init_type("u4", 4);

 phr.init_program_stack();

 phr.enter_lexical_scope();

 phr.reset_program_stack();

 phr.push_carrier_stack("fground");
 phr.hold_type_by_name("fbase");
 phr.push_carrier_symbol("&prn");

 phr.push_carrier_stack("lambda");
 phr.hold_type_by_name("u4");
 phr.push_carrier_raw_value("21");

 phr.coalesce_channel_group();
}

int main(int argc, char* argv[])
{
 PHR_Channel_System pcs;
 PhaonIR phr(&pcs);

 phr.init_type_system();
 phr.init_type("fbase", DEFAULT_PTR_BYTE_CODE);
 phr.init_type("u4", 4);

 phr.create_channel_semantic_protocol("lambda");
 phr.create_channel_semantic_protocol("result");

 phr.init_code_model();

 PHR_Code_Model& pcm = *phr.code_model();
 pcm.set_type_system(phr.type_system());

 phr.init_table();

 PHR_Runner phrn(&pcm);

 pcm.set_direct_eval_fn(&phr_direct_eval);

 PHR_Runtime_Scope prs(nullptr);

 PHR_Symbol_Scope pss(&prs);

 init_test_functions(phr, pcm, phrn.get_table(), pss);
 phrn.get_runtime_scope_queue().push_front(&prs);

 local_program(phr);

 PHR_Channel_Group* pcg = phr.get_select_channel_group();

 phrn.run(*pcg, phr.channel_system(), &pss);

 return 0;
}
