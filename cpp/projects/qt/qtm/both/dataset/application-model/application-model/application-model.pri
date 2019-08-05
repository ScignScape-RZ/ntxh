
#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

include(../build-group.pri)

QT += widgets network

INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR

INCLUDEPATH += $$PHAONIR_SRC_GROUP_DIR
INCLUDEPATH += $$SCIGNSTAGE_SRC_GROUP_DIR

DEFINES += CAON_DEBUG
DEFINES += RELAE_LABEL_NODES


CONFIG += no_keywords

DEFINES += USE_KANS
DEFINES += USE_RZNS



HEADERS += \
  $$SRC_DIR/application-config-model.h \
  $$SRC_DIR/application-model.h \
  $$SRC_DIR/application-test-model.h \

SOURCES += \
  $$SRC_DIR/application-config-model.cpp \
  $$SRC_DIR/application-model.cpp \
  $$SRC_DIR/application-test-model.cpp \


LIBS += -L$$TARGETSDIR -lScignStage-ling


contains(CHOICE_FEATURES, "kph") \#/
{
 message(DEFINE\'ing USING_KPH)
 DEFINES += USING_KPH
}

contains(CHOICE_FEATURES, "lex-pair") \#/
{
 message(DEFINE\'ing USING_LEXPAIR)
 DEFINES += USING_LEXPAIR
}

message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
