
#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)


include(../build-group.pri)

INCLUDEPATH += $$SRC_DIR
INCLUDEPATH += $$SRC_GROUP_DIR
INCLUDEPATH += $$SRC_GROUP_DIR/phr-graph-core


INCLUDEPATH += $$ANGELSCRIPT_SRC_GROUP_DIR
INCLUDEPATH += $$ANGELSCRIPT_SRC_GROUP_DIR/include

INCLUDEPATH += $$RELAE_GRAPH_SRC_GROUP_DIR

QMAKE_CXXFLAGS += -Wno-strict-aliasing

DEFINES += _CRT_SECURE_NO_WARNINGS

DEFINES += DEFAULT_PHR_GEN_FOLDER=\\\"$$SRC_ROOT_DIR/phra/gen\\\"

DEFINES += USE_RZNS
DEFINES += CAON_DEBUG
DEFINES += RELAE_LABEL_NODES


HEADERS += \
  $$SRC_DIR/phra-runner.h \
  $$SRC_DIR/phra-run-context.h \
  $$SRC_DIR/phra-graph-build.h \
  $$SRC_DIR/phra-runtime.h \
  $$SRC_DIR/phra-runtime-context.h \
  $$SRC_DIR/phra-binary-channel.h \


SOURCES += \
  $$SRC_DIR/phra-runner.cpp \
  $$SRC_DIR/phra-run-context.cpp \
  $$SRC_DIR/phra-graph-build.cpp \
  $$SRC_DIR/phra-runtime.cpp \
  $$SRC_DIR/phra-runtime-context.cpp \
  $$SRC_DIR/phra-binary-channel.cpp \


LIBS += -L$$TARGETSDIR -langelscript  -lphr-graph-core



message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
