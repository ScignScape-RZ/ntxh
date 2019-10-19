
#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = clo43sd-converter

include(../build-group.pri)

TEMPLATE = app

DESTDIR = $$QT_REPROZIP_BIN_DIR

INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR $$SRC_ROOT_DIR


CONFIG += no_keywords


HEADERS += \


SOURCES += \
  $$SRC_DIR/main.cpp \
