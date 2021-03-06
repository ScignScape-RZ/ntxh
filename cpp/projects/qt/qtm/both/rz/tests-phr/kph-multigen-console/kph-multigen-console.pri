
#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = kph-multigen-console

include(../build-group.pri)

TEMPLATE = app

INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR

INCLUDEPATH += $$PHAONIR_SRC_GROUP_DIR
INCLUDEPATH += $$PHAONLIB_SRC_GROUP_DIR

INCLUDEPATH += $$PHR_RUNTIME_SRC_GROUP_DIR


INCLUDEPATH += $$RELAE_GRAPH_SRC_GROUP_DIR

DEFINES += DEFAULT_PTR_BYTE_CODE=QT_POINTER_SIZE

DEFINES += USING_KPH_GEN

CONFIG += no_keywords

DEFINES += DEFAULT_KPH_FOLDER=\\\"$$CPP_ROOT_DIR/kph\\\"


HEADERS += \


SOURCES += \
  $$SRC_DIR/main.cpp \
  $$SRC_ROOT_DIR/default-phr-startup.cpp \


LIBS += -L$$TARGETSDIR -lkph-generator -lphaon-ir


message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
