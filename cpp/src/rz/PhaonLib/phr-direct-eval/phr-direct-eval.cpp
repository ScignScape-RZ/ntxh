
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "phr-direct-eval.h"

#include "phr-command-runtime/phr-command-runtime-router.h"

#include "defines.h"

#include "phaon-ir/phaon-ir.h"

#ifdef USING_KPH_GEN
#include "kph-generator/kph-generator.h"
#endif


#include "phaon-ir/scopes/phr-scope-system.h"
#include "phaon-ir/runtime/phr-command-package.h"

#include "phaon-ir/phr-code-model.h"

USING_KANS(Phaon)

KANS_(Phaon)

void phr_direct_eval(PHR_Code_Model* pcm,
  PHR_Command_Package* pcp, PHR_Symbol_Scope* pss)
{

#ifdef USING_KPH_GEN
 if(pcm->kph_generator())
 {
  KPH_Generator& gen = *pcm->kph_generator();
  QMap<QString, QString> docus;

  gen.encode(*pcp, docus);
  gen.save_kph_file();
  return;
 }
#endif // USING_KPH_GEN

 PHR_Scope_System* scope_system = pcm->scopes();
 if(pcp->bind_pto())
 {
  // //?
 }

 QString string_result;

 PHR_Command_Runtime_Router pcrr(pcm->table(),
   pcm->phaon_ir(), pss, scope_system, nullptr, string_result);

 pcrr.set_envv_fn(pcm->envv_fn());
 pcrr.parse_command_package(pcp);

 QString sfn = pcm->phaon_ir()->find_source_fn(pcrr.fground_name());
 if(!sfn.isEmpty())
 {
  pcm->phaon_ir()->run_callable_value(sfn);
 }
 else
 {
  pcrr.proceed();
 }

 const PHR_Type_Object* pto = pcrr.result_type_object();
 if(pto)
 {

  if(pcrr.string_result_code())
  {
   quint64 eval_result = pcrr.string_result_code();
   QString* qs = (QString*) eval_result;
   pcp->set_string_result(*qs);
   pcp->set_eval_result((quint64) pcp->string_result_as_pointer());
   pcp->set_result_type_object(pto);
  }
  else
  {
   quint64 eval_result = pcrr.call_result();

   pcp->set_eval_result(eval_result);
   pcp->set_result_type_object(pto);
  }
 }
}

_KANS(Phaon)
