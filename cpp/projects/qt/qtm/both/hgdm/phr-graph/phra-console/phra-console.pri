
#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

include(../build-group.pri)

TEMPLATE = app

INCLUDEPATH += $$SRC_GROUP_DIR

INCLUDEPATH += $$ANGELSCRIPT_SRC_GROUP_DIR
INCLUDEPATH += $$ANGELSCRIPT_SRC_GROUP_DIR/include

#INCLUDEPATH += $$SRC_GROUP_DIR/angelscript/add_on


DEFINES += CAON_DEBUG
DEFINES += RELAE_LABEL_NODES

DEFINES += PHRA_ROOT_DIR=\\\"$$ROOT_DIR/phra\\\"


CONFIG += no_keywords


message(SRC: $$SRC_DIR)

SOURCES += \
  $$SRC_DIR/main.cpp \



LIBS += -L$$TARGETSDIR -langelscript  -lphr-angel  \
  # -lphr-graph-core


message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)

