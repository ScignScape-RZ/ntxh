
#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = htxn

include(../build-group.pri)


INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR $$SRC_ROOT_DIR

INCLUDEPATH += $$WCM_SRC_GROUP_DIR
INCLUDEPATH += $$NTXH_SRC_GROUP_DIR
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


DEFINES += USE_KANS


HEADERS += \
  $$SRC_DIR/standard-glyphdeck-8b.h \
  $$SRC_DIR/standard-glyphpack-8b.h \
  $$SRC_DIR/glyph-argument-package.h \
  $$SRC_DIR/glyphdeck-base-8b.h \
  $$SRC_DIR/glyph-layers-8b.h \
  $$SRC_DIR/glyph-vector-8b.h \
  $$SRC_DIR/htxn-document-8b.h \


SOURCES += \
  $$SRC_DIR/standard-glyphdeck-8b.cpp \
  $$SRC_DIR/standard-glyphpack-8b.cpp \
  $$SRC_DIR/glyph-argument-package.cpp \
  $$SRC_DIR/glyphdeck-base-8b.cpp \
  $$SRC_DIR/glyph-layers-8b.cpp \
  $$SRC_DIR/glyph-vector-8b.cpp \
  $$SRC_DIR/htxn-document-8b.cpp \


#?
#LIBS += -L$$TARGETSDIR -lwcm -lntxh  \
#  -lntxh-parser -lclo43sd-data -lposit-lib


message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)

