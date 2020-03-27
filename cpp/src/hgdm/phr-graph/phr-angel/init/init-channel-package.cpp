
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phra-runner.h"

#include "angelscript/add_on/scriptstdstring/scriptstdstring.h"
#include "angelscript/add_on/scriptbuilder/scriptbuilder.h"

#include "phr-graph-core/kernel/graph/phr-graph.h"

#include "phr-graph-core/output/phr-graph-phr-output.h"
#include "phr-graph-core/kernel/graph/phr-graph-node.h"
#include "phr-graph-core/kernel/graph/phr-graph-connection.h"

#include "phr-graph-core/kernel/phr-graph-root.h"
#include "phr-graph-core/token/phr-graph-token.h"
#include "phr-graph-core/kernel/document/phr-graph-document.h"

#include "phr-graph-core/kernel/frame/phr-graph-frame.h"
#include "phr-graph-core/kernel/query/phr-graph-query.h"

#include "phra-run-context.h"
#include "phra-graph-build.h"

#include "contexts/phra-runtime-context.h"
#include "contexts/phra-value-context.h"
#include "contexts/phra-symbol-context.h"


#include "phra-runtime.h"

#include "channels/phra-channel-package.h"


void init_channel_package(asIScriptEngine& engine)
{
 int r = engine.RegisterObjectType("PHRA_Channel_Package", 0, asOBJ_REF); 
 assert( r >= 0 );

 r = engine.RegisterObjectBehaviour("PHRA_Channel_Package", asBEHAVE_ADDREF, "void f()", asMETHOD(PHRA_Channel_Package,add_ref), asCALL_THISCALL); 
 assert( r >= 0 );

 r = engine.RegisterObjectBehaviour("PHRA_Channel_Package", asBEHAVE_RELEASE, "void f()", asMETHOD(PHRA_Channel_Package,release), asCALL_THISCALL); 
 assert( r >= 0 );

 r = engine.RegisterObjectMethod("PHRA_Channel_Package", "PHRA_Carrier_Channel@ add_carrier_channel(const string &in)", asMETHOD(PHRA_Channel_Package,add_carrier_channel), asCALL_THISCALL); 
 assert( r >= 0 );

 r = engine.RegisterObjectMethod("PHRA_Channel_Package", "void add_fname(const string &in)", asMETHOD(PHRA_Channel_Package,add_fname), asCALL_THISCALL); 
 assert( r >= 0 );

// r = engine.RegisterObjectMethod("PHRA_Channel_Package", "void append(uint16)", asMETHODPR(PHRA_Binary_Channel,append,(u2),void), asCALL_THISCALL); 
// assert( r >= 0 );


}

