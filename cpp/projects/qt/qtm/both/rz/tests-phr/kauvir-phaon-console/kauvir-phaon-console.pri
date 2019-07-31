
#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = kauvir-phaon-console

include(../build-group.pri)



TEMPLATE = app

DEFINES += DEFAULT_KPH_FOLDER=\\\"$$CPP_ROOT_DIR/kph\\\"

DEFINES += DEFAULT_PTR_BYTE_CODE=QT_POINTER_SIZE

INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR
#INCLUDEPATH += $$KAUVIR_KCM_SRC_GROUP_DIR
INCLUDEPATH += $$HGDM_SRC_GROUP_DIR

INCLUDEPATH += $$RELAE_GRAPH_SRC_GROUP_DIR

INCLUDEPATH += $$PHAONLIB_SRC_GROUP_DIR
INCLUDEPATH += $$PHAONIR_SRC_GROUP_DIR

INCLUDEPATH += $$PHR_RUNTIME_SRC_GROUP_DIR

CONFIG += no_keywords


DEFINES += USE_KANS



INCLUDEPATH += $$KAUVIR_PHAON_SRC_GROUP_DIR
INCLUDEPATH += $$KAUVIR_KCM_SRC_GROUP_DIR
INCLUDEPATH += $$HGDM_SRC_GROUP_DIR
INCLUDEPATH += $$KCM_RUNTIME_EVAL_SRC_GROUP_DIR
INCLUDEPATH += $$KAUVIR_RUNTIME_SRC_GROUP_DIR
INCLUDEPATH += $$PHAON_SRC_GROUP_DIR


HEADERS += \
  $$SRC_DIR/test-functions.h \


SOURCES += \
  $$SRC_DIR/main.cpp \
  $$SRC_DIR/test-functions.cpp \

LIBS += -L$$TARGETSDIR -lphaon-ir -lphr-direct-eval  -lphr-fn-doc  \
   -lphr-command-runtime -lphr-env -lkph-generator

#LIBS += -L$$TARGETSDIR -lPhaonLib -lkauvir-code-model -lkauvir-type-system \
#  -lkcm-command-package -lkcm-direct-eval -lkcm-scopes \
#  -lkauvir-phaon -lkcm-command-runtime


contains(CHOICE_FEATURES, "kcm_ecl") \#/
{
 LIBS += -L$$TARGETSDIR -lkcm-lisp-bridge  -lrz-dynamo-generator
 include(../../../../find-ecl-sexp.pri)
 LIBS += -L$$ECL_DIR -lecl
 LIBS += -L$$CL_CXX_DIR/install/lib64 -lcl_cxx
}


contains(CHOICE_FEATURES, "iso-choice") \#/
{
 exists($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/kauvir--kauvir-kcm--kcm-lisp-bridge) \#/
 {
  LIBS += -L$$TARGETSDIR -lkcm-lisp-bridge -lrz-dynamo-generator
  message(DEFINE\'ing ISO__USING_ECL)
  DEFINES += ISO__USING_ECL
  include(../../../../find-ecl-sexp.pri)
  LIBS += -L$$ECL_DIR -lecl
  LIBS += -L$$CL_CXX_DIR/install/lib64 -lcl_cxx
 }
}


message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)