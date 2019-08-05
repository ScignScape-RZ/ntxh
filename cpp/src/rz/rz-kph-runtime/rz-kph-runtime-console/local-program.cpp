
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phaon-ir/phaon-ir.h"

#include "phaon-ir/phr-code-model.h"
#include "phaon-ir/scopes/phr-runtime-scope.h"

#include "phr-direct-eval/phr-direct-eval.h"
#include "phaon-ir/table/phr-symbol-scope.h"
#include "phaon-ir/table/phr-channel-group-table.h"

#include "default-basic-functions.h"

#include "phr-fn-doc/phr-fn-doc.h"
#include "phr-fn-doc/phr-fn-doc-multi.h"

#include "phr-env/phr-env.h"

#include "kph-generator/kph-generator-substitutions.h"
#include "kph-generator/kph-generator.h"

#include <QDebug>

extern void* insert_envv(void* kind, void* test);

USING_KANS(Phaon)


void local_program(PhaonIR& phr, QString phrf)
{
 phr.init_type_system();
 phr.init_type("fbase", DEFAULT_PTR_BYTE_CODE);
 phr.init_type("u4", 4);
 phr.init_type("u8", 8);
 phr.init_type("argvec", 9);
 phr.init_type("pcv", DEFAULT_PTR_BYTE_CODE);
 phr.init_type("str", DEFAULT_PTR_BYTE_CODE);
 phr.init_type("QString", DEFAULT_PTR_BYTE_CODE);

 phr.init_type("ScignStage_Ling_Dialog*", DEFAULT_PTR_BYTE_CODE);
 phr.init_type("Lexpair_Dialog*", DEFAULT_PTR_BYTE_CODE);


 qRegisterMetaType<PHR_Fn_Doc>();
 qRegisterMetaType<PHR_Fn_Doc*>();

 qRegisterMetaType<PHR_Fn_Doc_Multi>();
 qRegisterMetaType<PHR_Fn_Doc_Multi*>();

 // //  setup
 phr.init_code_model();

 PHR_Code_Model& pcm = *phr.code_model();
 pcm.set_type_system(phr.type_system());

 phr.create_channel_semantic_protocol("lambda");
 phr.create_channel_semantic_protocol("result");
 phr.create_channel_semantic_protocol("sigma");

 pcm.set_direct_eval_fn(&phr_direct_eval);

 pcm.create_and_register_type_object("PHR_Fn_Doc*");
 pcm.create_and_register_type_object("PHR_Fn_Doc_Multi*");

 PHR_Env* penv = new PHR_Env(&pcm);
 QString penv_typename = "PHR_Env*";
 insert_envv(&penv_typename, penv);

 pcm.create_and_register_type_object("PHR_Env*");

 penv->set_report_channel_group_fn([](PHR_Code_Model* pcm, PHR_Channel_Group* pcg)
  {
   QString qs;
   QTextStream qts(&qs);

   pcm->report_channel_group(qts, *pcg, pcm->detailed_report_synax(),
     PHR_Code_Model::Code_Environments::Statement);

   qDebug() << qs;
  });

 // //  this is specific to kph_gen ...
 penv->set_kph_gen_fn([](PHR_Code_Model* pcm, PHR_Channel_Group* pcg,
   QString subsstr, QString fn, QString* text, QMap<QString, QString> docus)
 {
  KPH_Generator_Substitutions subs(subsstr);

  if(text)
  {
   KPH_Generator gen;
   gen.encode(*pcg, docus, fn);
   *text = gen.text();
  }
  else
  {
   KPH_Generator gen (DEFAULT_KPH_FOLDER "/gen/rz-kph/t1.txt", &subs);
   gen.encode(*pcg, docus, fn);
   gen.save_kph_file();
  }
 });



 PHR_Runtime_Scope prs(nullptr);

 PHR_Symbol_Scope pss(&prs);

 phr.init_table();

 init_basic_functions(phr, pcm, *phr.table(), pss);

 phr.hold_symbol_scope(&pss);

 // //  setup
 phr.read_local_program(phrf); //RZ_DIR "/phaon/cc/t1.rz.gen.pgb.phr");
}

