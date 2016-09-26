#-------------------------------------------------
#
# Project created by QtCreator 2016-09-26T15:25:03
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_rangeiteratortest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_rangeiteratortest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

unix|win32: LIBS += -L$$OUT_PWD/../../../src/common/ -lcommon

INCLUDEPATH += $$PWD/../../../src/common
DEPENDPATH += $$PWD/../../../src/common
