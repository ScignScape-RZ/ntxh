
#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = clo43sd-data

include(../build-group.pri)

INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR $$SRC_ROOT_DIR

INCLUDEPATH += $$WCM_SRC_GROUP_DIR
INCLUDEPATH += $$NTXH_SRC_GROUP_DIR
INCLUDEPATH += $$NTXH_SRC_GROUP_DIR/ntxh
INCLUDEPATH += $$PHAON_GRAPH_SRC_GROUP_DIR
INCLUDEPATH += $$RELAE_GRAPH_SRC_GROUP_DIR

DEFINES += DEFAULT_WCM_FOLDER=\\\"$$DATA_ROOT_DIR/wcm\\\"

DEFINES += CLO43SD_ROOT_FOLDER=\\\"$$ROOT_DIR/../xd/clo43sd/CLO-43SD\\\"

CONFIG += no_keywords


DEFINES += USE_KANS


HEADERS += \
  $$SRC_DIR/clo-species.h \
  $$SRC_DIR/clo-species-display-info.h \
  $$SRC_DIR/clo-file.h \
  $$SRC_DIR/clo-database.h \


SOURCES += \
  $$SRC_DIR/clo-species.cpp \
  $$SRC_DIR/clo-species-display-info.cpp \
  $$SRC_DIR/clo-file.cpp \
  $$SRC_DIR/clo-database.cpp \


#?
LIBS += -L$$TARGETSDIR -lwcm -lntxh -lntxh-parser


message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)

