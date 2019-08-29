#PROJECT_NAME = endo-npy

#include(../build-group.pri)



INCLUDEPATH += /home/nlevisrael/hypergr/ntxh/ar/cpp/src

USING_KANS

QT += widgets

HEADERS += \
  ./cnpy.h \
  ./npy.hpp \


SOURCES += \
  ./cnpy.cpp \
  ./main.cpp \

LIBS += -lz


