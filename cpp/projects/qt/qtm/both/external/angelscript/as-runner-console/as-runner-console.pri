
#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

include(../build-group.pri)

TEMPLATE = app

INCLUDEPATH += $$SRC_GROUP_DIR
INCLUDEPATH += $$SRC_GROUP_DIR/include

#INCLUDEPATH += $$SRC_GROUP_DIR/angelscript/add_on


DEFINES += CAON_DEBUG
DEFINES += RELAE_LABEL_NODES

DEFINES += AS_ROOT_DIR=\\\"$$ROOT_DIR/as\\\"


CONFIG += no_keywords

SOURCES += \
  $$SRC_DIR/main.cpp \



LIBS += -L$$TARGETSDIR -langelscript  -las-runner  #-lpdf-pull -ldsmain


#?contains(CHOICE_FEATURES, "pdf-pull") \#/
#?{
#? message(DEFINE\'ing USING_PDF_PULL)
#? DEFINES += USING_PDF_PULL
#? LIBS +=-L$$TARGETSDIR -lpdf-pull  \
#?   -ldsmain -lntxh -lntxh-builder -lntxh-parser
#?}


message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)

