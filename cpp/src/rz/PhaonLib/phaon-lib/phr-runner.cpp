
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "phr-runner.h"

#include "phaon-ir/table/phr-symbol-scope.h"
#include "phaon-ir/table/phr-function-vector.h"

#include "phaon-ir/table/phr-channel-group-table.h"

#include "phaon-ir/scopes/phr-scope-system.h"
#include "phaon-ir/phr-code-model.h"

#include "phaon-ir/runtime/phr-command-package.h"


USING_KANS(Phaon)


PHR_Runner::PHR_Runner(PHR_Code_Model* pcm)
  :  pcm_(pcm), origin_(nullptr),
    table_(nullptr)
{
 table_ = pcm_->table();
 scopes_ = pcm_->scopes();
}

void PHR_Runner::init(PHR_Code_Model* pcm)
{
}

void PHR_Runner::run(PHR_Channel_Group& pcg, PHR_Channel_System* pcs, PHR_Symbol_Scope* pss)
{
 PHR_Command_Package pcp(pcg, pcs, pcm_->type_system());
 pcm_->direct_eval(&pcp, pss);
}

void PHR_Runner::run(PHR_Command_Package& pcp, PHR_Symbol_Scope* pss)
{
 pcm_->direct_eval(&pcp, pss);
}

QQueue<PHR_Runtime_Scope*>& PHR_Runner::get_runtime_scope_queue()
{
 return scopes_->phr_scope_queue();
}

