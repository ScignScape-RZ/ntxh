
#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

include(../build-group.pri)

QT += widgets

TEMPLATE = app

INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR

INCLUDEPATH += $$SCIGNSTAGE_SRC_GROUP_DIR
INCLUDEPATH += $$APPLICATION_MODEL_SRC_GROUP_DIR
INCLUDEPATH += $$CONFIG_SRC_GROUP_DIR
INCLUDEPATH += $$PHAONIR_SRC_GROUP_DIR
INCLUDEPATH += $$PHAON_GRAPH_SRC_GROUP_DIR
INCLUDEPATH += $$RELAE_GRAPH_SRC_GROUP_DIR
INCLUDEPATH += $$LEXPAIR_SRC_GROUP_DIR
INCLUDEPATH += $$PHAONLIB_SRC_GROUP_DIR
INCLUDEPATH += $$QRING_SRC_GROUP_DIR

DEFINES += DEFAULT_RPH_FOLDER=\\\"$$DATA_ROOT_DIR/rph\\\"

DEFINES += CAON_DEBUG
DEFINES += RELAE_LABEL_NODES

DEFINES += DATA_FOLDER=\\\"$$DATA_ROOT_DIR\\\"

DEFINES += DEFAULT_NTXH_FOLDER=\\\"$$DATA_ROOT_DIR/ntxh\\\"

DEFINES += SCREENSHOTS_FOLDER=\\\"$$ROOT_DIR/screenshots\\\"
DEFINES += DEFAULT_ICON_FOLDER=\\\"$$CPP_ROOT_DIR/assets/icons\\\"

DEFINES += DEFINES_SRC_FOLDER=\\\"$$SRC_ROOT_DIR/_defines\\\"
DEFINES += CHOICES_PRI_FOLDER=\\\"$$CPP_ROOT_DIR/projects/qt/qtm/_choices\\\"
DEFINES += CUSTOM_LIBS_PRI_FOLDER=\\\"$$CPP_ROOT_DIR/projects/qt/qtm/_custom_libs\\\"
DEFINES += UNIBUILD_PRI_FOLDER=\\\"$$CPP_ROOT_DIR/projects/qt/qtm/unibuild\\\"

DEFINES += USE_KANS
DEFINES += USE_RZNS
DEFINES += USE_QSNS


HEADERS += \
  $$SRC_DIR/test-functions.h \


SOURCES += \
  $$SRC_DIR/main.cpp \
  $$SRC_DIR/test-functions.cpp \


LIBS += -L$$TARGETSDIR  -ldsmain  -lScignStage-ling  \
  -lntxh  -lntxh-parser  -lntxh-builder  \
  -lapplication-model  -lqring

contains(CHOICE_FEATURES, "config") \#/
{
 message(DEFINE\'ing USING_CONFIG_DIALOG)
 DEFINES += USING_CONFIG_DIALOG
 LIBS += -L$$TARGETSDIR  -lconfig-dialog
}

contains(CHOICE_FEATURES, "xpdf") \#/
{
 message(DEFINE\'ing USE_XPDF)
 DEFINES += USE_XPDF
 LIBS += -L$$TARGETSDIR -lxpdf -lfreetype
 # or  -lqtfreetyped  -lqtlibpngd
}

contains(CHOICE_FEATURES, "kph") \#/
{
 message(DEFINE\'ing USING_KPH)
 DEFINES += USING_KPH
 LIBS += -L$$TARGETSDIR -lphaon-lib -lphaon-ir -lphr-direct-eval  \
   -lphr-command-runtime
}

contains(CHOICE_FEATURES, "kph-gen") \#/
{
 LIBS += -L$$TARGETSDIR -lkph-generator

}

contains(CHOICE_FEATURES, "lex-pair") \#/
{
 message(DEFINE\'ing USING_LEXPAIR)
 DEFINES += USING_LEXPAIR
 LIBS += -L$$TARGETSDIR -llexpair
}


message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
