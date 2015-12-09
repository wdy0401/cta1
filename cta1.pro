#-------------------------------------------------
#
# Project created by QtCreator 2015-01-06T16:22:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cta1
TEMPLATE = SUBDIRS
#TEMPLATE = app


SOURCES += main.cpp\
	mainwindow.cpp \
	../gpp_qt/wfunction/wfunction.cpp \
    ../gpp_qt/cmd_line/cmd_line.cpp \
    ../gpp_qt/log_info/log_info.cpp \
    ../gpp_qt/log_info/logs.cpp \
    ../gpp_qt/wfunction/qtfunction.cpp

HEADERS  += mainwindow.h \
	order.h \
    parameter.h \
	../gpp_qt/wfunction/wfunction.h \
    ../gpp_qt/cmd_line/cmd_line.h \
    ../gpp_qt/log_info/log_info.h \
    ../gpp_qt/log_info/logs.h \
    ../gpp_qt/wfunction/qtfunction.h

FORMS    += mainwindow.ui

SUBDIRS += \
	datafeed \
	fillpolicy \
	orderbook \
	match_engine \
	snapshot \
        tactic


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-cta1-Desktop_Qt_5_3_MSVC2013_32bit-Release/datafeed/release/ -ldatafeed
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-cta1-Desktop_Qt_5_3_MSVC2013_32bit-Release/datafeed/debug/ -ldatafeed

INCLUDEPATH += $$PWD/../build-cta1-Desktop_Qt_5_3_MSVC2013_32bit-Release/datafeed/release
DEPENDPATH += $$PWD/../build-cta1-Desktop_Qt_5_3_MSVC2013_32bit-Release/datafeed/release

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-cta1-Desktop_Qt_5_3_MSVC2013_32bit-Release/fillpolicy/release/ -lfillpolicy
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-cta1-Desktop_Qt_5_3_MSVC2013_32bit-Release/fillpolicy/debug/ -lfillpolicy

INCLUDEPATH += $$PWD/../build-cta1-Desktop_Qt_5_3_MSVC2013_32bit-Release/fillpolicy/release
DEPENDPATH += $$PWD/../build-cta1-Desktop_Qt_5_3_MSVC2013_32bit-Release/fillpolicy/release

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-cta1-Desktop_Qt_5_3_MSVC2013_32bit-Release/orderbook/release/ -lorderbook
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-cta1-Desktop_Qt_5_3_MSVC2013_32bit-Release/orderbook/debug/ -lorderbook

INCLUDEPATH += $$PWD/../build-cta1-Desktop_Qt_5_3_MSVC2013_32bit-Release/orderbook/release
DEPENDPATH += $$PWD/../build-cta1-Desktop_Qt_5_3_MSVC2013_32bit-Release/orderbook/release

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-cta1-Desktop_Qt_5_3_MSVC2013_32bit-Release/match_engine/release/ -lmatch_engine
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-cta1-Desktop_Qt_5_3_MSVC2013_32bit-Release/match_engine/debug/ -lmatch_engine

INCLUDEPATH += $$PWD/../build-cta1-Desktop_Qt_5_3_MSVC2013_32bit-Release/match_engine/release
DEPENDPATH += $$PWD/../build-cta1-Desktop_Qt_5_3_MSVC2013_32bit-Release/match_engine/release

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-cta1-Desktop_Qt_5_3_MSVC2013_32bit-Release/snapshot/release/ -lsnapshot
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-cta1-Desktop_Qt_5_3_MSVC2013_32bit-Release/snapshot/debug/ -lsnapshot

INCLUDEPATH += $$PWD/../build-cta1-Desktop_Qt_5_3_MSVC2013_32bit-Release/snapshot/release
DEPENDPATH += $$PWD/../build-cta1-Desktop_Qt_5_3_MSVC2013_32bit-Release/snapshot/release

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-cta1-Desktop_Qt_5_3_MSVC2013_32bit-Release/tactic/release/ -ltactic
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-cta1-Desktop_Qt_5_3_MSVC2013_32bit-Release/tactic/debug/ -ltactic

INCLUDEPATH += $$PWD/../build-cta1-Desktop_Qt_5_3_MSVC2013_32bit-Release/tactic/release
DEPENDPATH += $$PWD/../build-cta1-Desktop_Qt_5_3_MSVC2013_32bit-Release/tactic/release
