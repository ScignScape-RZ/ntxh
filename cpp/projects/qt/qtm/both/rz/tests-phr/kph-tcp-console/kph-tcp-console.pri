
#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = kph-tcp-console

include(../build-group.pri)

QT += network

#

TEMPLATE = app

DEFINES += DEFAULT_KPH_FOLDER=\\\"$$CPP_ROOT_DIR/kph\\\"


INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR

INCLUDEPATH += $$PHAONIR_SRC_GROUP_DIR
INCLUDEPATH += $$PHAONLIB_SRC_GROUP_DIR

INCLUDEPATH += $$PHR_RUNTIME_SRC_GROUP_DIR
INCLUDEPATH += $$RELAE_GRAPH_SRC_GROUP_DIR

#/home/nlevisrael/hypergr/ntxh/ar/cpp/src/hgdm/relae-graph/relae-graph/relae-caon-ptr.h


CONFIG += no_keywords


DEFINES += USE_KANS

DEFINES += DEFAULT_PTR_BYTE_CODE=QT_POINTER_SIZE

#INCLUDEPATH += $$SRC_ROOT_DIR/phaon/phaon


#INCLUDEPATH += $$KAUVIR_KCM_SRC_GROUP_DIR \
#  $$KAUVIR_KCM_SRC_GROUP_DIR/kauvir-type-system \
#  $$KAUVIR_KCM_SRC_GROUP_DIR/kauvir-code-model


SOURCES += \
  $$SRC_DIR/main.cpp \
  $$SRC_ROOT_DIR/default-phr-startup.cpp \


LIBS += -L$$TARGETSDIR -lphaon-ir

#LIBS += -L$$TARGETSDIR -lPhaonLib -lkauvir-code-model -lkauvir-type-system \
#  -lkcm-command-package -lkcm-direct-eval -lkcm-scopes \
#  -lkauvir-phaon -lkcm-command-runtime


contains(CHOICE_FEATURES, "kph") \#/
{
 message(DEFINE\'ing USING_KPH)
 DEFINES += USING_KPH
#?? LIBS += -L$$TARGETSDIR -lphaon-lib -lphaon-ir

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
