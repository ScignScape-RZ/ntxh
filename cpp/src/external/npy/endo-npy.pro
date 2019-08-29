#PROJECT_NAME = endo-npy

#include(../build-group.pri)


QT += widgets

HEADERS += \
  ./cnpy.h \
  ./npy.hpp \


SOURCES += \
  ./cnpy.cpp \
  ./main.cpp \

LIBS += -lz


