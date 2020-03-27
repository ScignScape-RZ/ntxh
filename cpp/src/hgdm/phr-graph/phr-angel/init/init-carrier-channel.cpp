
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

#include "channels/phra-carrier-channel.h"



void init_carrier_channel(asIScriptEngine& engine)
{
 int r = engine.RegisterObjectType("PHRA_Carrier_Channel", 0, asOBJ_REF); 
 assert( r >= 0 );

 r = engine.RegisterObjectBehaviour("PHRA_Carrier_Channel", asBEHAVE_ADDREF, "void f()", asMETHOD(PHRA_Carrier_Channel,add_ref), asCALL_THISCALL); 
 assert( r >= 0 );

 r = engine.RegisterObjectBehaviour("PHRA_Carrier_Channel", asBEHAVE_RELEASE, "void f()", asMETHOD(PHRA_Carrier_Channel,release), asCALL_THISCALL); 
 assert( r >= 0 );

 r = engine.RegisterObjectMethod("PHRA_Carrier_Channel","void add_carrier(const string& in, const string& in, uint8 loc)", asMETHODPR(PHRA_Carrier_Channel,add_carrier,(const std::string&, const std::string&, u1),void), asCALL_THISCALL); 
 assert( r >= 0 );

 r = engine.RegisterObjectMethod("PHRA_Carrier_Channel","PHRA_Binary_Channel@ to_binary(PHRA_Value_Context@)", asMETHOD(PHRA_Carrier_Channel,to_binary), asCALL_THISCALL); 
 assert( r >= 0 );
 
}

