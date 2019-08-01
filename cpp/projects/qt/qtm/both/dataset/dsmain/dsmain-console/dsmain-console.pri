
#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

include(../build-group.pri)

QT += widgets

TEMPLATE = app

INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR

INCLUDEPATH += $$SCIGNSTAGE_SRC_GROUP_DIR

#INCLUDEPATH += $$KAUVIR_KCM_SRC_GROUP_DIR
#INCLUDEPATH += $$PHAON_SRC_GROUP_DIR
#INCLUDEPATH += $$QHYP_SRC_GROUP_DIR
#INCLUDEPATH += $$KCM_RUNTIME_EVAL_SRC_GROUP_DIR
#INCLUDEPATH += $$KAUVIR_RUNTIME_SRC_GROUP_DIR
#INCLUDEPATH += $$LEXPAIR_SRC_GROUP_DIR

INCLUDEPATH += $$APPLICATION_MODEL_SRC_GROUP_DIR
INCLUDEPATH += $$CONFIG_SRC_GROUP_DIR

INCLUDEPATH += $$PHAONIR_SRC_GROUP_DIR

INCLUDEPATH += $$PHAON_GRAPH_SRC_GROUP_DIR
INCLUDEPATH += $$RELAE_GRAPH_SRC_GROUP_DIR

INCLUDEPATH += $$LEXPAIR_SRC_GROUP_DIR

INCLUDEPATH += $$PHAONLIB_SRC_GROUP_DIR


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


#DEFINES += USING_XPDF


HEADERS += \
  $$SRC_DIR/test-functions.h \


SOURCES += \
  $$SRC_DIR/main.cpp \
  $$SRC_DIR/test-functions.cpp \


LIBS += -L$$TARGETSDIR  -ldsmain  -lScignStage-ling  \
  -lntxh  -lntxh-parser  -lntxh-builder  \  #  -lxpdf  -lfreetype
  -lapplication-model


#  -lrph-builder -lrelae-phaon    -lds-relae-phaon



#? -lapplication-model  -lconfig-dialog

#? LIBS += -L$$TARGETSDIR -llexpair


contains(CHOICE_FEATURES, "config") \#/
{
 message(DEFINE\'ing USING_CONFIG_DIALOG)
 DEFINES += USING_CONFIG_DIALOG
 LIBS += -L$$TARGETSDIR -lapplication-model  -lconfig-dialog
# LIBS += -L$$TARGETSDIR -lpdf-pull
}


contains(CHOICE_FEATURES, "xpdf") \#/
{
 message(DEFINE\'ing USE_XPDF)
 DEFINES += USE_XPDF
 LIBS += -L$$TARGETSDIR -lxpdf -lfreetype
# LIBS += -L$$TARGETSDIR -lpdf-pull
}

contains(CHOICE_FEATURES, "kph") \#/
{
 message(DEFINE\'ing USING_KPH)
 DEFINES += USING_KPH
 LIBS += -L$$TARGETSDIR -lphaon-lib -lphaon-ir -lphr-direct-eval  \
   -lphr-command-runtime

#? LIBS += -L$$TARGETSDIR -lkcm-direct-eval -lkcm-scopes  \
#?   -lkauvir-phaon -lPhaonLib -lkauvir-code-model \
#?   -lkcm-command-runtime -lkcm-command-package -lkauvir-type-system
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


contains(CHOICE_FEATURES, "kcm_ecl") \#/
{
#? LIBS += -L$$TARGETSDIR -lkcm-lisp-bridge -lrz-dynamo-generator
#? include(../../../../find-ecl-sexp.pri)
#? LIBS += -L$$ECL_DIR -lecl
#? LIBS += -L$$CL_CXX_DIR/install/lib64 -lcl_cxx
}

contains(CHOICE_FEATURES, "iso-choice") \#/
{
 exists($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/external--xpdf--xpdf) \#/
 {
  message(DEFINE\'ing ISO__USING_XPDF)
  DEFINES += ISO__USING_XPDF
  LIBS += -L$$TARGETSDIR -lxpdf -lpdf-pull
 }

 exists($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/tests-kph--kauvir-phaon--kauvir-phaon) \#/
 {
  message(DEFINE\'ing ISO__USING_KPH)
  DEFINES += ISO__USING_KPH
  LIBS += -L$$TARGETSDIR -lkcm-direct-eval -lkcm-scopes  \
    -lkauvir-phaon -lPhaonLib -lkauvir-code-model \
    -lkcm-command-runtime -lkcm-command-package -lkauvir-type-system
 }

 exists($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/kauvir--kauvir-kcm--kcm-lisp-bridge) \#/
 {
  message(DEFINE\'ing ISO__USING_ECL)
  DEFINES += ISO__USING_ECL
  include(../../../../find-ecl-sexp.pri)
  LIBS += -L$$ECL_DIR
  LIBS += -L$$CL_CXX_DIR/install/lib64 -lcl_cxx
 }
}

message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
