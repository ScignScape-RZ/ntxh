
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

#include "channels/phra-binary-channel.h"

void init_value_context(asIScriptEngine& engine)
{
 int r = engine.RegisterObjectType("PHRA_Value_Context", 0, asOBJ_REF); 
 assert( r >= 0 );

 r = engine.RegisterObjectBehaviour("PHRA_Value_Context", asBEHAVE_ADDREF, "void f()", asMETHOD(PHRA_Value_Context,add_ref), asCALL_THISCALL); 
 assert( r >= 0 );

 r = engine.RegisterObjectBehaviour("PHRA_Value_Context", asBEHAVE_RELEASE, "void f()", asMETHOD(PHRA_Value_Context,release), asCALL_THISCALL); 
 assert( r >= 0 );

 
 r = engine.RegisterObjectMethod("PHRA_Value_Context", "void merge_binary_channel(PHRA_Binary_Channel@, uint8, uint64)", asMETHOD(PHRA_Value_Context,merge_binary_channel), asCALL_THISCALL); 
 assert( r >= 0 );

 r = engine.RegisterObjectMethod("PHRA_Value_Context", "uint8 get1v(uint8)", asMETHOD(PHRA_Value_Context,get1v), asCALL_THISCALL); 
 assert( r >= 0 );

 r = engine.RegisterObjectMethod("PHRA_Value_Context", "uint16 get2v(uint8)", asMETHOD(PHRA_Value_Context,get2v), asCALL_THISCALL); 
 assert( r >= 0 );

 r = engine.RegisterObjectMethod("PHRA_Value_Context", "uint32 get4v(uint8)", asMETHOD(PHRA_Value_Context,get4v), asCALL_THISCALL); 
 assert( r >= 0 );

 r = engine.RegisterObjectMethod("PHRA_Value_Context", "uint64 get8v(uint8)", asMETHOD(PHRA_Value_Context,get8v), asCALL_THISCALL); 
 assert( r >= 0 );


 r = engine.RegisterObjectMethod("PHRA_Value_Context", "uint8 loc1(uint8)", asMETHOD(PHRA_Value_Context,loc1), asCALL_THISCALL); 
 assert( r >= 0 );

 r = engine.RegisterObjectMethod("PHRA_Value_Context", "uint8 loc2(uint16)", asMETHOD(PHRA_Value_Context,loc2), asCALL_THISCALL); 
 assert( r >= 0 );

 r = engine.RegisterObjectMethod("PHRA_Value_Context", "uint8 loc4(uint32)", asMETHOD(PHRA_Value_Context,loc4), asCALL_THISCALL); 
 assert( r >= 0 );

 r = engine.RegisterObjectMethod("PHRA_Value_Context", "uint8 loc8(uint64)", asMETHOD(PHRA_Value_Context,loc8), asCALL_THISCALL); 
 assert( r >= 0 );

}

