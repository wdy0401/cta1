QT       -= gui

TARGET = datafeed
TEMPLATE = lib

DEFINES += DATAFEED_LIBRARY

SOURCES += datafeed.cpp \
    ../../gpp_qt/wfunction/wfunction.cpp

HEADERS += datafeed.h\
		datafeed_global.h \
    ../../gpp_qt/wfunction/wfunction.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
