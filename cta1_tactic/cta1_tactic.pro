
QT       -= gui

TARGET = cta1_tactic
TEMPLATE = lib

DEFINES += TACTIC_LIBRARY

SOURCES += cta1_tactic.cpp \


HEADERS += cta1_tactic.h\
                cta1_tactic_global.h \


unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../build-cta1-Desktop_Qt_5_3_MSVC2013_32bit-Release/match_engine/release/ -lmatch_engine
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build-cta1-Desktop_Qt_5_3_MSVC2013_32bit-Release/match_engine/debug/ -lmatch_engine

INCLUDEPATH += $$PWD/../../build-cta1-Desktop_Qt_5_3_MSVC2013_32bit-Release/match_engine/release
DEPENDPATH += $$PWD/../../build-cta1-Desktop_Qt_5_3_MSVC2013_32bit-Release/match_engine/release
