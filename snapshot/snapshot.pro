
QT       -= gui

TARGET = snapshot
TEMPLATE = lib

DEFINES += SNAPSHOT_LIBRARY

SOURCES += snapshot.cpp

HEADERS += snapshot.h\
		snapshot_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
