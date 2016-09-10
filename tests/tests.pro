#-------------------------------------------------
#
# Project created by QtCreator 2016-09-11T00:06:53
#
#-------------------------------------------------

QT       += testlib

TARGET = tst_cannytest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES +=
DEFINES += SRCDIR=\\\"$$PWD/\\\"

unix|win32: LIBS += -L$$OUT_PWD/../src/common/ -lcommon

INCLUDEPATH += $$PWD/../src/common
DEPENDPATH += $$PWD/../src/common
