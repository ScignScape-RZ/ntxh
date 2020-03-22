
#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)


include(../build-group.pri)

INCLUDEPATH += $$SRC_DIR
INCLUDEPATH += $$SRC_GROUP_DIR
#INCLUDEPATH += $$SRC_GROUP_DIR/include

INCLUDEPATH += $$ANGELSCRIPT_SRC_GROUP_DIR
INCLUDEPATH += $$ANGELSCRIPT_SRC_GROUP_DIR/include

QMAKE_CXXFLAGS += -Wno-strict-aliasing

DEFINES += _CRT_SECURE_NO_WARNINGS


HEADERS += \
  $$SRC_DIR/phra-runner.h \

SOURCES += \
  $$SRC_DIR/phra-runner.cpp \


LIBS += -L$$TARGETSDIR -langelscript



message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
