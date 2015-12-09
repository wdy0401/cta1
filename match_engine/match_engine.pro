
QT       -= gui

TARGET = match_engine
TEMPLATE = lib

DEFINES += MATCH_ENGINE_LIBRARY

SOURCES += match_engine.cpp \
    ../../gpp_qt/wfunction/wfunction.cpp

HEADERS += match_engine.h\
		match_engine_global.h \
    ../../gpp_qt/wfunction/wfunction.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
