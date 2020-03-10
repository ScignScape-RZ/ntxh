
#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = ngml-sdi

include(../build-group.pri)

INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR $$SRC_ROOT_DIR

INCLUDEPATH += $$NTXH_SRC_GROUP_DIR

INCLUDEPATH += $$HTXN_SRC_GROUP_DIR

INCLUDEPATH += $$NTXH_SRC_GROUP_DIR/ntxh
INCLUDEPATH += $$PHAON_GRAPH_SRC_GROUP_DIR
INCLUDEPATH += $$RELAE_GRAPH_SRC_GROUP_DIR


DEFINES += DEFAULT_WCM_FOLDER=\\\"$$DATA_ROOT_DIR/wcm\\\"

DEFINES += DEFAULT_NTXH_FOLDER=\\\"$$DATA_ROOT_DIR/ntxh\\\"

DEFINES += QT_REPROZIP_BIN_FOLDER=\\\"$$QT_REPROZIP_BIN_DIR\\\"

#DEFINES += CLO43SD_ROOT_FOLDER=\\\"$$ROOT_DIR/../external/data/clo43sd/CLO-43SD\\\"

DEFINES += ROOT_FOLDER=\\\"$$ROOT_DIR\\\"

DEFINES += CLO43SD_DB_CODE=\\\"222\\\"


CONFIG += no_keywords

DEFINES += CAON_DEBUG

DEFINES += USE_KANS
DEFINES += USE_RZNS
DEFINES += RELAE_LABEL_NODES


HEADERS += \
  $$SRC_DIR/ngml-sdi-document.h \
  $$SRC_DIR/ngml-sdi-mark-base.h \
  $$SRC_DIR/ngml-sdi-mark-generic.h \
  $$SRC_DIR/ngml-sdi-paragraph.h \
  $$SRC_DIR/ngml-sdi-sentence.h \


SOURCES += \
  $$SRC_DIR/ngml-sdi-document.cpp \
  $$SRC_DIR/ngml-sdi-mark-base.cpp \
  $$SRC_DIR/ngml-sdi-mark-generic.cpp \
  $$SRC_DIR/ngml-sdi-paragraph.cpp \
  $$SRC_DIR/ngml-sdi-sentence.cpp \


LIBS += -L$$TARGETSDIR -lntxh


#?
#LIBS += -L$$TARGETSDIR -lwcm -lntxh  \
#  -lntxh-parser -lclo43sd-data -lposit-lib


message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)

