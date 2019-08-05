
#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = phr-command-runtime


include(../build-group.pri)

DEFINES += USE_KANS


INCLUDEPATH += $$SRC_GROUP_DIR


INCLUDEPATH += $$HGDM_SRC_GROUP_DIR

INCLUDEPATH += $$PHAONIR_SRC_GROUP_DIR
INCLUDEPATH += $$RELAE_GRAPH_SRC_GROUP_DIR
INCLUDEPATH += $$PHR_RUNTIME_SRC_GROUP_DIR


HEADERS +=  \
  $$SRC_DIR/phr-command-runtime-router.h \
  $$SRC_DIR/phr-command-runtime-argument.h \
  $$SRC_DIR/phr-command-runtime-table.h \
  $$SRC_DIR/phr-command-runtime-router-qob.h \
  $$SRC_DIR/phr-command-runtime-router-cast-schedule.h \


SOURCES +=  \
  $$SRC_DIR/phr-command-runtime-router.cpp \
  $$SRC_DIR/phr-command-runtime-argument.cpp \
  $$SRC_DIR/phr-command-runtime-table.cpp \

CONFIG += no_keywords

LIBS += -L$$TARGETSDIR -lphaon-ir -lphaon-lib  -lphr-fn-doc



message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
