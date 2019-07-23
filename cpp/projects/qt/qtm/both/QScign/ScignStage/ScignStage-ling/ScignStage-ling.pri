
#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)


QT += widgets network


INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR

INCLUDEPATH += $$DSMAIN_SRC_GROUP_DIR

INCLUDEPATH += $$XPDF_SRC_GROUP_DIR
INCLUDEPATH += $$PHAON_SRC_GROUP_DIR

#INCLUDEPATH += $$QHYP_SRC_GROUP_DIR
#INCLUDEPATH += $$KAUVIR_PHAON_SRC_GROUP_DIR
#INCLUDEPATH += $$KAUVIR_KCM_SRC_GROUP_DIR

INCLUDEPATH += $$PHAON_GRAPH_SRC_GROUP_DIR
INCLUDEPATH += $$RELAE_GRAPH_SRC_GROUP_DIR

#INCLUDEPATH += $$LEXPAIR_SRC_GROUP_DIR

INCLUDEPATH += $$HGDM_SRC_GROUP_DIR

INCLUDEPATH += $$XPDF_SRC_GROUP_DIR/xpdf/aconf
INCLUDEPATH += $$XPDF_SRC_GROUP_DIR/xpdf/goo

DEFINES += CAON_DEBUG
DEFINES += RELAE_LABEL_NODES

DEFINES += DEFAULT_FOLDER=\\\"$$CPP_ROOT_DIR/assets\\\"
DEFINES += DEFAULT_ICON_FOLDER=\\\"$$CPP_ROOT_DIR/assets/icons\\\"

DEFINES += ABOUT_FILE_FOLDER=\\\"$$CPP_ROOT_DIR/about/about-files\\\"

DEFINES += SAMPLES_FOLDER=\\\"$$DATA_ROOT_DIR/samples\\\"


CONFIG += no_keywords

DEFINES += USE_KANS
DEFINES += USE_RZNS

#DEFINES += USING_XPDF
INCLUDEPATH += $$XPDF_SRC_GROUP_DIR


HEADERS += \
  $$SRC_DIR/ScignStage-ling-dialog.h \
  $$SRC_DIR/nav-protocols/nav-ling-1d-panel.h \
  $$SRC_DIR/subwindows/scignstage-clickable-label.h \
  $$SRC_DIR/xpdf-bridge.h \


SOURCES += \
  $$SRC_DIR/ScignStage-ling-dialog.cpp \
  $$SRC_DIR/nav-protocols/nav-ling-1d-panel.cpp \
  $$SRC_DIR/subwindows/scignstage-clickable-label.cpp \
  $$SRC_DIR/xpdf-bridge.cpp \
  $$SRC_ROOT_DIR/add-minimize-frame.cpp \



LIBS += -L$$TARGETSDIR -ldsmain


contains(CHOICE_FEATURES, "xpdf") \#/
{
 message(LINKING XPDF)
 LIBS += -L$$TARGETSDIR -lxpdf
}

contains(CHOICE_FEATURES, "kph") \#/
{
 #?message(DEFINE\'ing USING_KPH)
 #?DEFINES += USING_KPH
 LIBS += -L$$TARGETSDIR -lPhaonLib -lkauvir-phaon -lkauvir-code-model
}

contains(CHOICE_FEATURES, "iso-choice") \#/
{
 exists($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/external--xpdf--xpdf) \#/
 {
  message(DEFINE\'ing USING_XPDF)
  DEFINES += USING_XPDF
  LIBS += -L$$TARGETSDIR -lxpdf
 }

 exists($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/tests-kph--kauvir-phaon--kauvir-phaon) \#/
 {
  message(DEFINE\'ing USING_XPDF)
  DEFINES += USING_KPH
  LIBS += -L$$TARGETSDIR -lPhaonLib -lkauvir-phaon -lkauvir-code-model
 }
}



#LIBS += -L$$TARGETSDIR -llexpair


message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
