
#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)


PROJECT_NAME = ntxh-udp

include(../build-group.pri)

INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR

INCLUDEPATH += $$UDPIPE_SRC_GROUP_DIR
INCLUDEPATH += $$QRING_SRC_GROUP_DIR
INCLUDEPATH += $$NTXH_SRC_GROUP_DIR
INCLUDEPATH += $$RELAE_GRAPH_SRC_GROUP_DIR
INCLUDEPATH += $$NTXH_SRC_GROUP_DIR/ntxh
INCLUDEPATH += $$PHAON_GRAPH_SRC_GROUP_DIR

INCLUDEPATH += $$UDPIPE_SRC_GROUP_DIR/udpipe


CONFIG += no_keywords


DEFINES += USE_KANS


HEADERS += \
    $$SRC_DIR/ntxh-udp-sentence.h \
    $$SRC_DIR/ntxh-udp-corpus.h \


SOURCES += \
    $$SRC_DIR/ntxh-udp-sentence.cpp \
    $$SRC_DIR/ntxh-udp-corpus.cpp \



LIBS += -L$$TARGETSDIR -ludpipe -lqring


