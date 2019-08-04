
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "rz-graph-visit/rz-graph-visitor-phaon.h"


#include <QtEndian>

#include <QtGlobal>
#include <QtCore>

#include <QDebug>

#include "rzns.h"

#include "rz-graph-core/kernel/document/rz-re-document.h"
#include "rz-graph-core/output/rz-re-pre-normal-lisp.h"

#include "rz-graph-code/prerun/rz-re-prerun-tokens.h"
#include "rz-graph-code/prerun/rz-re-prerun-normalize.h"
#include "rz-graph-code/prerun/rz-re-prerun-anticipate.h"

#include "rz-graph-visit/rz-lisp-graph-visitor.h"
#include "rz-code-generators/rpi/rpi-output.h"

#include "phr-graph-core/kernel/graph/phr-graph.h"
#include "phr-graph-core/kernel/graph/phr-graph-build.h"

#include "phr-graph-core/output/phr-graph-phr-output.h"
#include "phr-graph-core/kernel/document/phr-graph-document.h"

#include "phr-graph-core/kernel/graph/pgb-ir-build.h"

//?#include "phr-graph-core/kernel/graph/pgb-ir-run.h"

#include "kans.h"


#include "phaon-ir/phaon-ir.h"

#include "phaon-ir/eval/phr-channel-group-evaluator.h"
#include "phaon-ir/eval/phr-minimal-evaluator.h"

#include "phaon-ir/channel/phr-channel-system.h"

#include <QDebug>


#include "phr-direct-eval/phr-direct-eval.h"

#include <functional>
#include <QDebug>


#include "textio.h"
USING_KANS(TextIO)

USING_RZNS(RECore)

USING_KANS(Phaon)


QString compile_rz(QString file_name)
{
 QString result;

 RE_Document* doc = new RE_Document(file_name);
 doc->parse();

 doc->report_graph(file_name + ".txt");

 RE_Pre_Normal_Lisp prenorm(doc);
 prenorm.output("..prenorm.txt");

 RE_Prerun_Tokens tokens(doc);
 tokens.output("..prenorm2.txt");


 RE_Prerun_Normalize normalize(*doc->graph());


 caon_ptr<RZ_Lisp_Graph_Visitor> visitor = normalize.scan();

 visitor->set_document_directory(doc->local_directory());

 RZ_Graph_Visitor_Phaon visitor_phaon(*visitor);
 RPI_Output rpo(visitor_phaon);

 doc->report_graph(file_name + ".re1.txt");

 RE_Pre_Normal_Lisp prenorm1(doc);
 prenorm1.output("..prenorm1.txt");

 RE_Prerun_Anticipate anticipate(*visitor, doc->local_path() + ".cprs");

 anticipate.scan(nullptr);//[](RZ_Dynamo_Output& rzdo){rzdo.init_top_level_block();});

 anticipate.run_core_pairs_generations();

 PGB_IR_Build pgb(file_name + ".gen.pgb");

 rpo.build_phaon_graph(pgb);

 pgb.generate_file(rpo.step_forms());

 PHR_Graph phg;
 PHR_Graph_Build phgb(phg);

 phgb.load_from_pgb_file(pgb.out_file());
 PHR_Graph_PHR_Output pgo(pgb.out_file() + ".phr");
 pgo.document()->set_graph(&phg);
 pgo.generate();

 return pgb.out_file() + ".phr";

}


extern void local_program(PhaonIR& phr, QStringList& progs, QString topl);
extern void local_program(PhaonIR& phr, QString phrf);

PHR_Channel_Group_Evaluator* load_evaluator(PhaonIR& phr, PHR_Channel_Group& pcg)
{
 QString fname = phr.get_first_raw_value_string("fground", pcg);
 if(fname.startsWith('#'))
 {
  PHR_Minimal_Evaluator::Kernal_Operators kop =
    PHR_Minimal_Evaluator::parse_kernel_operator(fname);
  if(kop != PHR_Minimal_Evaluator::Kernal_Operators::N_A)
  {
   PHR_Minimal_Evaluator* result = new PHR_Minimal_Evaluator(phr, pcg);
   result->set_kernel_operator(kop);
   return result;
  }
 }
 return nullptr;
}

void run_phaon(QStringList& progs, QString topl)
{
 PHR_Channel_System pcs;

 for(QString prog : progs)
 {
  PhaonIR phr(&pcs);

  phr.set_load_evaluator_fn(&load_evaluator);
  phr.set_direct_eval_fn(&phr_direct_eval);

  qDebug() << "\nLocal " << prog;
  local_program(phr, prog);
  //local_program(phr, progs, topl);

 }

// PhaonIR phr(&pcs);

// phr.set_load_evaluator_fn(&load_evaluator);
// phr.set_direct_eval_fn(&phr_direct_eval);
// local_program(phr, progs, topl);
}



int main(int argc, char* argv[])
{
 QString lines = load_file(RZ_DIR "/demo/multi/m1.txt");

 QStringList qsl = lines.split('\n');

 QStringList fns;

 for(QString line : qsl)
 {
  QString fn = line.simplified();
  if(fn.isEmpty())
    continue;
  if(fn.startsWith(';'))
    continue;
  if(fn.startsWith('#'))
    continue;
  QRegularExpressionMatch rxm;
  if(fn.indexOf(QRegularExpression("\\(\\s*(\\d+)\\s*-\\s*(\\d+)\\s*\\)"), 0, &rxm))
  {
   int sn = rxm.captured(1).toInt();
   int en = rxm.captured(2).toInt();
   int s = rxm.capturedStart();
   int e = rxm.capturedEnd();
   for(int i = sn; i <= en; ++i)
   {
    QString nfn = fn;
    nfn.replace(s, e-s, QString::number(i));
    fns.push_back(nfn.prepend(RZ_DIR "/demo/multi/"));
   }
   continue;
  }
  fns.push_back(fn.prepend(RZ_DIR "/demo/multi/"));
 }

 QStringList phrfs;
 for(QString fn : fns)
 {
  QString phrf = compile_rz(fn);
  phrfs.push_back(phrf);
 }

 run_phaon(phrfs, RZ_DIR "/demo/multi/m1.txt");
 return 0;
}

