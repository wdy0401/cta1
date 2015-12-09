
QT       -= gui

TARGET = optionf
TEMPLATE = lib

DEFINES += OPTIONF_LIBRARY

SOURCES += optionf.cpp \
    ../../gpp_qt/wfunction/wmath.cpp

HEADERS += optionf.h\
		optionf_global.h\
	../../gpp_qt/wfunction/wmath.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
