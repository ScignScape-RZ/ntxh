
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phra-graph-build.h"

#include "phr-graph-core/kernel/graph/phr-graph.h"

#include "phr-graph-core/output/phr-graph-phr-output.h"
#include "phr-graph-core/kernel/graph/phr-graph-node.h"
#include "phr-graph-core/kernel/graph/phr-graph-connection.h"

#include "phr-graph-core/kernel/phr-graph-root.h"
#include "phr-graph-core/token/phr-graph-token.h"
#include "phr-graph-core/kernel/document/phr-graph-document.h"

#include "phr-graph-core/kernel/frame/phr-graph-frame.h"
#include "phr-graph-core/kernel/query/phr-graph-query.h"

PHRA_Graph_Build::PHRA_Graph_Build()
  :  fr_(PHR_Graph_Frame::instance()),
     qy_(PHR_Graph_Query::instance()), 
     phr_graph_(nullptr), phr_out_(nullptr),
     ref_count_(0)
{
}

void PHRA_Graph_Build::test()
{
 qDebug() << "test ...";
}

void PHRA_Graph_Build::add_ref()
{
 // Increase the reference counter
 ref_count_++;
}
 
void PHRA_Graph_Build::release()
{
 // Decrease ref count and delete if it reaches 0
 if( --ref_count_ == 0 )
   delete this;
}

void PHRA_Graph_Build::init_graph()
{
 phr_graph_ = new PHR_Graph;

 phr_out_ = new PHR_Graph_PHR_Output(DEFAULT_PHR_GEN_FOLDER "/t1.phr");

 phr_out_->document()->set_graph(phr_graph_);

 caon_ptr<PHR_Graph_Root> rt = new PHR_Graph_Root(phr_out_->document().raw_pointer());
 caon_ptr<PHR_Graph_Node> rn = new PHR_Graph_Node(rt);

 phr_graph_->set_root_node(rn);

 qDebug() << "GR Init";
}


