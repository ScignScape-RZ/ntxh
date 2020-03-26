
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



#ifdef HIDE

 r = engine.RegisterObjectType("PHRA_Symbol_Context", 0, asOBJ_REF); assert( r >= 0 );

 r = engine.RegisterObjectBehaviour("PHRA_Symbol_Context", asBEHAVE_ADDREF, "void f()", asMETHOD(PHRA_Symbol_Context,add_ref), asCALL_THISCALL); assert( r >= 0 );

 r = engine.RegisterObjectBehaviour("PHRA_Symbol_Context", asBEHAVE_RELEASE, "void f()", asMETHOD(PHRA_Symbol_Context,release), asCALL_THISCALL); assert( r >= 0 );


 r = engine.RegisterObjectType("PHRA_Runtime_Context", 0, asOBJ_REF); assert( r >= 0 );

 r = engine.RegisterObjectBehaviour("PHRA_Runtime_Context", asBEHAVE_ADDREF, "void f()", asMETHOD(PHRA_Runtime_Context,add_ref), asCALL_THISCALL); assert( r >= 0 );

 r = engine.RegisterObjectBehaviour("PHRA_Runtime_Context", asBEHAVE_RELEASE, "void f()", asMETHOD(PHRA_Runtime_Context,release), asCALL_THISCALL); assert( r >= 0 );

 r = engine.RegisterGlobalFunction("PHRA_Runtime_Context@ new_rt_context()", asFUNCTION(new_rt_context), asCALL_CDECL); 
 assert( r >= 0 );

 r = engine.RegisterObjectMethod("PHRA_Runtime_Context", "PHRA_Value_Context@ init_value_context()", asMETHOD(PHRA_Runtime_Context,init_value_context), asCALL_THISCALL); 
 assert( r >= 0 );

 r = engine.RegisterObjectMethod("PHRA_Runtime_Context", "PHRA_Symbol_Context@ init_symbol_context()", asMETHOD(PHRA_Runtime_Context,init_symbol_context), asCALL_THISCALL); 
 assert( r >= 0 );



 r = engine.RegisterObjectType("PHRA_Runtime", 0, asOBJ_REF); assert( r >= 0 );

 r = engine.RegisterObjectBehaviour("PHRA_Runtime", asBEHAVE_ADDREF, "void f()", asMETHOD(PHRA_Runtime,add_ref), asCALL_THISCALL); assert( r >= 0 );

 r = engine.RegisterObjectBehaviour("PHRA_Runtime", asBEHAVE_RELEASE, "void f()", asMETHOD(PHRA_Runtime,release), asCALL_THISCALL); assert( r >= 0 );


 r = engine.RegisterObjectType("PHRA_Binary_Channel", 0, asOBJ_REF); assert( r >= 0 );


 r = engine.RegisterObjectBehaviour("PHRA_Binary_Channel", asBEHAVE_ADDREF, "void f()", asMETHOD(PHRA_Binary_Channel,add_ref), asCALL_THISCALL); assert( r >= 0 );

 r = engine.RegisterObjectBehaviour("PHRA_Binary_Channel", asBEHAVE_RELEASE, "void f()", asMETHOD(PHRA_Binary_Channel,release), asCALL_THISCALL); assert( r >= 0 );

 r = engine.RegisterObjectMethod("PHRA_Binary_Channel", "void set_kind(const string &in)", asMETHODPR(PHRA_Binary_Channel,set_kind,(const std::string&),void), asCALL_THISCALL); 
 assert( r >= 0 );

 r = engine.RegisterObjectMethod("PHRA_Binary_Channel", "void append(uint8)", asMETHODPR(PHRA_Binary_Channel,append,(u1),void), asCALL_THISCALL); 
 assert( r >= 0 );

 r = engine.RegisterObjectMethod("PHRA_Binary_Channel", "void append(uint16)", asMETHODPR(PHRA_Binary_Channel,append,(u2),void), asCALL_THISCALL); 
 assert( r >= 0 );

 r = engine.RegisterObjectMethod("PHRA_Binary_Channel", "void append(uint32)", asMETHODPR(PHRA_Binary_Channel,append,(u4),void), asCALL_THISCALL); 
 assert( r >= 0 );

 r = engine.RegisterObjectMethod("PHRA_Binary_Channel", "void append(uint64)", asMETHODPR(PHRA_Binary_Channel,append,(u8),void), asCALL_THISCALL); 
 assert( r >= 0 );

 r = engine.RegisterObjectMethod("PHRA_Binary_Channel", "void test_extract(uint16, uint8)", asMETHODPR(PHRA_Binary_Channel,test_extract,(u2,u1),void), asCALL_THISCALL); 
 assert( r >= 0 );

 r = engine.RegisterGlobalFunction("PHRA_Binary_Channel@ new_binary_channel()", asFUNCTION(new_binary_channel), asCALL_CDECL); 
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

#endif // def HIDE

}

