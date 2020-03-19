

#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

include(../build-group.pri)

INCLUDEPATH += $$SRC_DIR
INCLUDEPATH += $$SRC_GROUP_DIR/include

QMAKE_CXXFLAGS += -Wno-strict-aliasing

DEFINES += _CRT_SECURE_NO_WARNINGS


HEADERS += $$SRC_GROUP_DIR/include/angelscript.h \
           $$SRC_DIR/source/as_array.h \
           $$SRC_DIR/source/as_atomic.h \
           $$SRC_DIR/source/as_builder.h \
           $$SRC_DIR/source/as_bytecode.h \
           $$SRC_DIR/source/as_callfunc.h \
           $$SRC_DIR/source/as_compiler.h \
           $$SRC_DIR/source/as_config.h \
           $$SRC_DIR/source/as_configgroup.h \
           $$SRC_DIR/source/as_context.h \
           $$SRC_DIR/source/as_criticalsection.h \   
           $$SRC_DIR/source/as_datatype.h \
           $$SRC_DIR/source/as_debug.h \
           $$SRC_DIR/source/as_gc.h \ 
           $$SRC_DIR/source/as_generic.h \
           $$SRC_DIR/source/as_map.h \
           $$SRC_DIR/source/as_memory.h \
           $$SRC_DIR/source/as_module.h \
           $$SRC_DIR/source/as_objecttype.h \
           $$SRC_DIR/source/as_outputbuffer.h \
           $$SRC_DIR/source/as_parser.h \
           $$SRC_DIR/source/as_property.h \
           $$SRC_DIR/source/as_restore.h \
           $$SRC_DIR/source/as_scriptcode.h \
           $$SRC_DIR/source/as_scriptengine.h \
           $$SRC_DIR/source/as_scriptfunction.h \
           $$SRC_DIR/source/as_scriptnode.h \
           $$SRC_DIR/source/as_scriptobject.h \
           $$SRC_DIR/source/as_string.h \
           $$SRC_DIR/source/as_string_util.h \
           $$SRC_DIR/source/as_symboltable.h \   
           $$SRC_DIR/source/as_texts.h \
           $$SRC_DIR/source/as_thread.h \
           $$SRC_DIR/source/as_tokendef.h \
           $$SRC_DIR/source/as_tokenizer.h \
           $$SRC_DIR/source/as_typeinfo.h \
           $$SRC_DIR/source/as_variablescope.h

SOURCES += $$SRC_DIR/source/as_atomic.cpp \
           $$SRC_DIR/source/as_builder.cpp \
           $$SRC_DIR/source/as_bytecode.cpp \
           $$SRC_DIR/source/as_callfunc.cpp \
           $$SRC_DIR/source/as_callfunc_mips.cpp \
           $$SRC_DIR/source/as_callfunc_ppc.cpp \
           $$SRC_DIR/source/as_callfunc_ppc_64.cpp \
           $$SRC_DIR/source/as_callfunc_sh4.cpp \
           $$SRC_DIR/source/as_callfunc_x64_gcc.cpp \
           $$SRC_DIR/source/as_callfunc_x64_mingw.cpp \
           $$SRC_DIR/source/as_callfunc_x64_msvc.cpp \
           $$SRC_DIR/source/as_callfunc_x86.cpp \
           $$SRC_DIR/source/as_callfunc_xenon.cpp \
           $$SRC_DIR/source/as_compiler.cpp \
           $$SRC_DIR/source/as_configgroup.cpp \
           $$SRC_DIR/source/as_context.cpp \
           $$SRC_DIR/source/as_datatype.cpp \
           $$SRC_DIR/source/as_gc.cpp \
           $$SRC_DIR/source/as_generic.cpp \
           $$SRC_DIR/source/as_globalproperty.cpp \
           $$SRC_DIR/source/as_memory.cpp \
           $$SRC_DIR/source/as_module.cpp \
           $$SRC_DIR/source/as_objecttype.cpp \
           $$SRC_DIR/source/as_outputbuffer.cpp \
           $$SRC_DIR/source/as_parser.cpp \
           $$SRC_DIR/source/as_restore.cpp \
           $$SRC_DIR/source/as_scriptcode.cpp \
           $$SRC_DIR/source/as_scriptengine.cpp \
           $$SRC_DIR/source/as_scriptfunction.cpp \
           $$SRC_DIR/source/as_scriptnode.cpp \
           $$SRC_DIR/source/as_scriptobject.cpp \
           $$SRC_DIR/source/as_string.cpp \
           $$SRC_DIR/source/as_string_util.cpp \
           $$SRC_DIR/source/as_thread.cpp \
           $$SRC_DIR/source/as_tokenizer.cpp \
           $$SRC_DIR/source/as_typeinfo.cpp \
           $$SRC_DIR/source/as_variablescope.cpp

HEADERS += $$SRC_DIR/add_on/scriptany/scriptany.h \
           $$SRC_DIR/add_on/scriptarray/scriptarray.h \
           $$SRC_DIR/add_on/scriptdictionary/scriptdictionary.h \
           $$SRC_DIR/add_on/scriptmath/scriptmath.h \
           $$SRC_DIR/add_on/scripthandle/scripthandle.h \
           $$SRC_DIR/add_on/scriptstdstring/scriptstdstring.h \
           $$SRC_DIR/add_on/scriptbuilder/scriptbuilder.h

SOURCES += $$SRC_DIR/add_on/scriptany/scriptany.cpp \
           $$SRC_DIR/add_on/scriptarray/scriptarray.cpp \
           $$SRC_DIR/add_on/scriptdictionary/scriptdictionary.cpp \
           $$SRC_DIR/add_on/scriptmath/scriptmath.cpp \
           $$SRC_DIR/add_on/scripthandle/scripthandle.cpp \
           $$SRC_DIR/add_on/scriptstdstring/scriptstdstring.cpp \
           $$SRC_DIR/add_on/scriptstdstring/scriptstdstring_utils.cpp \
           $$SRC_DIR/add_on/scriptbuilder/scriptbuilder.cpp


!win32-g++:win32:contains(QMAKE_HOST.arch, x86_64):{
    asm_compiler.commands = ml64 /c
    asm_compiler.commands +=  /Fo ${QMAKE_FILE_OUT} ${QMAKE_FILE_IN}
    asm_compiler.output = ${QMAKE_VAR_OBJECTS_DIR}${QMAKE_FILE_BASE}$${first(QMAKE_EXT_OBJ)}
    asm_compiler.input = ASM_SOURCES
    asm_compiler.variable_out = OBJECTS
    asm_compiler.name = compiling[asm] ${QMAKE_FILE_IN}
    silent:asm_compiler.commands = @echo compiling[asm] ${QMAKE_FILE_IN} && $$asm_compiler.commands
    QMAKE_EXTRA_COMPILERS += asm_compiler

    ASM_SOURCES += \
        $$PWD/angelscript/source/as_callfunc_x64_msvc_asm.asm
		
    if(win32-msvc2008|win32-msvc2010):equals(TEMPLATE_PREFIX, "vc") {
        SOURCES += \
            $$PWD/angelscript/source/as_callfunc_x64_msvc_asm.asm
    }
}



message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
