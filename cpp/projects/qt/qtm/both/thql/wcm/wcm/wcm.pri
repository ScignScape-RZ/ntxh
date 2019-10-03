
#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = wcm

include(../build-group.pri)


INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR $$SRC_ROOT_DIR


CONFIG += no_keywords

DEFINES += USE_KANS


HEADERS += \
  $$SRC_DIR/wcm-database.h \
  $$SRC_DIR/wcm-column.h \
  $$SRC_DIR/wcm-column-set.h \
  $$SRC_DIR/wcm-record.h \
  $$SRC_DIR/wcm-hypernode.h \
  $$SRC_DIR/wcm-hyponode.h \
  $$SRC_DIR/wcm-type.h \
  $$SRC_DIR/whitedb/_whitedb.h


SOURCES += \
  $$SRC_DIR/wcm-database.cpp \
  $$SRC_DIR/wcm-column.cpp \
  $$SRC_DIR/wcm-column-set.cpp \
  $$SRC_DIR/wcm-record.cpp \
  $$SRC_DIR/wcm-hypernode.cpp \
  $$SRC_DIR/wcm-hyponode.cpp \
  $$SRC_DIR/wcm-type.cpp \
  $$SRC_DIR/whitedb/_whitedb.c

#?LIBS += -L$$TARGETSDIR -lrelae-phaon


message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)

