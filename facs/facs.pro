
QT += widgets core 

INCLUDEPATH += \
 ./gui \


HEADERS += \
 ./gui/MainWindow.h  \


SOURCES +=  \
 ./gui/MainWindow.cpp  \
 ./gui/ViewsListWidget.cpp  \
 ./gui/QtProgramInfo.cpp  \
 ./gui/ProfileChannelWidget.cpp  \
 ./gui/GraphExportWindow.cpp  \
 ./gui/GatesListWidget.cpp \   # skip calc thread ...
 ./gui/FacsanaduProject.cpp \
 ./gui/DialogAbout.cpp \
 ./gui/DatasetListWidget.cpp \






#


OBJECTS_DIR = ./build/objects
DESTDIR = ./build/dest
TARGETSDIR = ./build/targets


