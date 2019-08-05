
#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = phr-direct-eval

include(../build-group.pri)

DEFINES += USE_KANS

INCLUDEPATH += $$PHAONIR_SRC_GROUP_DIR
INCLUDEPATH += $$PHAONLIB_SRC_GROUP_DIR

INCLUDEPATH += $$TESTS_PHR_SRC_GROUP_DIR


CONFIG += no_keywords


HEADERS +=  \
  $$SRC_DIR/phr-direct-eval.h \

SOURCES +=  \
  $$SRC_DIR/phr-direct-eval.cpp \


LIBS += -L$$TARGETSDIR -lphaon-ir -lphr-command-runtime



contains(CHOICE_FEATURES, "kph-gen") \#/
{
 message(DEFINE\'ing USING_KPH_GEN)
 DEFINES += USING_KPH_GEN
 LIBS += -L$$TARGETSDIR -lkph-generator
}

message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
