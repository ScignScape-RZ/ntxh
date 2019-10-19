
QT       += core

CONFIG   += console

TEMPLATE = lib



####  These regex matches should identify the pertinent directories and
##    build settings for Qt and qmake, based on the qmake output directory
##    (assuming you're using shadow build).  If not, a workaround would be
##    to set some of these constants by hand (most of these constants
##    are set assuming a common directory structure underneath ROOT_DIR).
##    To see the settings obtained from these substitutions,
##    uncomment the "message" lines below.

ROOT_DIR = $$OUT_PWD

ROOT_DIR ~= s!/cpp/projects.qt/.*!!

DEFINES += WHICH_DEFINES=\\\"./_defines/$${WHICH_BUILD_DIR_CODE}_defines.h\\\"


## this is defined elswhere now ...
#BUILD_DIR_CODE = $$OUT_PWD
#BUILD_DIR_CODE ~= s!.*/(build|release)-($$PROJECT_NAME)-(.*)-(Debug|Release)!\3


#message($$ROOT_DIR)
#message($$BUILD_DIR_CODE)

TARGET_QT_VERSION = $$QT_VERSION

TARGET_QT_VERSION ~= s/\./-

TARGET_CODE = $$TARGET_QT_VERSION-$$BUILD_DIR_CODE

TARGET_NUM = targets-$${TARGET_CODE}

CPP_ROOT_DIR = $$ROOT_DIR/cpp

DATA_ROOT_DIR = $$ROOT_DIR/data

PROJECTS_ROOT_DIR = $$CPP_ROOT_DIR/projects

QT_PROJECTS_ROOT_DIR = $$PROJECTS_ROOT_DIR/qt

PROJECTS_DIR = $$QT_PROJECTS_ROOT_DIR/qt$$TARGET_CODE

SRC_ROOT_DIR = $$CPP_ROOT_DIR/src

SRC_GLOBAL_DIR = $$CPP_ROOT_DIR/src/global

SRC_PROSET_DIR = $$SRC_ROOT_DIR/$$PROJECT_SET

SRC_GROUP_DIR = $$SRC_PROSET_DIR/$$PROJECT_GROUP

SRC_DIR = $$SRC_GROUP_DIR/$$PROJECT_NAME

TARGET = $$PROJECT_NAME

TARGETS_ROOT_DIR = $$CPP_ROOT_DIR/targets/qt/qt-multiple

TARGETSDIR = $$TARGETS_ROOT_DIR/$$TARGET_NUM


CONFIG(debug, debug|release) {
    OBJECTS_DIR = $$TARGETSDIR/PROJECT_OBJECTS/$$PROJECT_NAME/debug
} else {
    OBJECTS_DIR = $$TARGETSDIR/PROJECT_OBJECTS/$$PROJECT_NAME/release
}


DESTDIR = $$TARGETSDIR


INCLUDEPATH += $$SRC_DIR $$SRC_ROOT_DIR $$SRC_GLOBAL_DIR

#INCLUDEPATH += $$PHR_GRAPH_SRC_GROUP_DIR

QT_REPROZIP_SRC_DIR = $$SRC_ROOT_DIR/qt-reprozip
QT_REPROZIP_BIN_DIR = $$QT_REPROZIP_SRC_DIR/bin

#groups
QRING_SRC_GROUP_DIR = $$SRC_ROOT_DIR/QScign/QRing
RELAE_GRAPH_SRC_GROUP_DIR = $$SRC_ROOT_DIR/hgdm/relae-graph
PHAON_GRAPH_SRC_GROUP_DIR = $$SRC_ROOT_DIR/hgdm/phaon-graph
NTXH_SRC_GROUP_DIR = $$SRC_ROOT_DIR/hgdm/ntxh
DSMAIN_SRC_GROUP_DIR = $$SRC_ROOT_DIR/dataset/dsmain
SCIGNSTAGE_SRC_GROUP_DIR = $$SRC_ROOT_DIR/QScign/ScignStage
XPDF_SRC_GROUP_DIR = $$SRC_ROOT_DIR/external/xpdf
APPLICATION_MODEL_SRC_GROUP_DIR = $$SRC_ROOT_DIR/dataset/application-model
CONFIG_SRC_GROUP_DIR = $$SRC_ROOT_DIR/dataset/config
UDPIPE_SRC_GROUP_DIR = $$SRC_ROOT_DIR/external/udpipe
PHR_GRAPH_SRC_GROUP_DIR = $$SRC_ROOT_DIR/hgdm/phr-graph
RELAE_GRAPH_SRC_GROUP_DIR = $$SRC_ROOT_DIR/hgdm/relae-graph
PHAONIR_SRC_GROUP_DIR = $$SRC_ROOT_DIR/rz/PhaonIR
RZ_KAUVIR_SRC_GROUP_DIR = $$SRC_ROOT_DIR/rz/rz-kauvir
PHAONLIB_SRC_GROUP_DIR = $$SRC_ROOT_DIR/rz/PhaonLib
PHR_RUNTIME_SRC_GROUP_DIR = $$SRC_ROOT_DIR/rz/phr-runtime
TESTS_PHR_SRC_GROUP_DIR = $$SRC_ROOT_DIR/rz/tests-phr
WCM_SRC_GROUP_DIR = $$SRC_ROOT_DIR/thql/wcm

LEXPAIR_SRC_GROUP_DIR = $$SRC_ROOT_DIR/QScign/LexPair

