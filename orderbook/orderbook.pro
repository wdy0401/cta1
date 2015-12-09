
QT       -= gui

TARGET = orderbook
TEMPLATE = lib

DEFINES += ORDERBOOK_LIBRARY

SOURCES += orderbook.cpp

HEADERS += orderbook.h\
		orderbook_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
