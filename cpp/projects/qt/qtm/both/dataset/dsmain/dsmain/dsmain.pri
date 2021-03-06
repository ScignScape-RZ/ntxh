
#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

include(../build-group.pri)

INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR
#INCLUDEPATH += $$KAUVIR_KCM_SRC_GROUP_DIR $$KAUVIR_KCM_SRC_GROUP_DIR/kcm-lisp-bridge
#INCLUDEPATH += $$PHAON_GRAPH_SRC_GROUP_DIR


INCLUDEPATH += $$NTXH_SRC_GROUP_DIR/ntxh
INCLUDEPATH += $$NTXH_SRC_GROUP_DIR
#exists($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/kauvir--kauvir-kcm--kcm-lisp-bridge) \#/
#{
# INCLUDEPATH += $$SEXP_DIR
# INCLUDEPATH += $$SEXP_DIR/pingus/
#}


DEFINES += CAON_DEBUG
DEFINES += RELAE_LABEL_NODES


INCLUDEPATH += $$HGDM_SRC_GROUP_DIR

INCLUDEPATH += $$RELAE_GRAPH_SRC_GROUP_DIR
INCLUDEPATH += $$HGDM_SRC_GROUP_DIR/relae-phaon
INCLUDEPATH += $$PHAON_GRAPH_SRC_GROUP_DIR

INCLUDEPATH += $$QRING_SRC_GROUP_DIR

DEFINES += AR_ROOT_DIR=\\\"$$ROOT_DIR\\\"

CONFIG += no_keywords

DEFINES += USE_KANS
#?DEFINES += USE_RZNS



HEADERS += \
  $$SRC_DIR/language-sample.h \
  $$SRC_DIR/language-sample-group.h \
  $$SRC_DIR/dataset.h \


SOURCES += \
  $$SRC_DIR/language-sample.cpp \
  $$SRC_DIR/language-sample-group.cpp \
  $$SRC_DIR/dataset.cpp \

 LIBS += -L$$TARGETSDIR   -lntxh   \
  -lntxh-parser -lntxh-builder -lqring


message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
