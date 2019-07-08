
#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = ntxh-parser

include(../build-group.pri)


INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR $$SRC_ROOT_DIR

INCLUDEPATH += $$RELAE_GRAPH_SRC_GROUP_DIR
INCLUDEPATH += $$SRC_GROUP_DIR/ntxh
INCLUDEPATH += $$PHAON_GRAPH_SRC_GROUP_DIR


CONFIG += no_keywords

DEFINES += USE_KANS


HEADERS += \
  $$SRC_DIR/grammar/ntxh-graph-build.h \
  $$SRC_DIR/grammar/ntxh-grammar.h \
  $$SRC_DIR/grammar/ntxh-parse-context.h \
  $$SRC_DIR/grammar/ntxh-parser.h \
  $$SRC_DIR/ntxh-document.h \


SOURCES += \
  $$SRC_DIR/grammar/ntxh-graph-build.cpp \
  $$SRC_DIR/grammar/ntxh-grammar.cpp \
  $$SRC_DIR/grammar/ntxh-parse-context.cpp \
  $$SRC_DIR/grammar/ntxh-parser.cpp \
  $$SRC_DIR/ntxh-document.cpp \



LIBS += -L$$TARGETSDIR -lntxh


message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)

