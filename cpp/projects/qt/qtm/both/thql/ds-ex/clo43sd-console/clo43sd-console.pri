
#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = clo43sd-console

include(../build-group.pri)

TEMPLATE = app

QT += multimedia widgets

INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR $$SRC_ROOT_DIR

INCLUDEPATH += $$WCM_SRC_GROUP_DIR
INCLUDEPATH += $$NTXH_SRC_GROUP_DIR
INCLUDEPATH += $$NTXH_SRC_GROUP_DIR/ntxh
INCLUDEPATH += $$PHAON_GRAPH_SRC_GROUP_DIR
INCLUDEPATH += $$RELAE_GRAPH_SRC_GROUP_DIR

DEFINES += DEFAULT_WCM_FOLDER=\\\"$$DATA_ROOT_DIR/wcm\\\"

DEFINES += DEFAULT_AUDIO_FOLDER=\\\"$$ROOT_DIR/../external/data/clo43sd/CLO-43SD-AUDIO/audio\\\"

DEFINES += CLO43SD_DB_CODE=\\\"222\\\"

CONFIG += no_keywords


DEFINES += USE_KANS


HEADERS += \


SOURCES += \
  $$SRC_DIR/main.cpp \



#?
LIBS += -L$$TARGETSDIR -lwcm -lntxh -lntxh-parser \
 -lclo43sd-data  -lScignStage-audio


message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)

