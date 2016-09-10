#-------------------------------------------------
#
# Project created by QtCreator 2016-09-11T00:06:53
#
#-------------------------------------------------


TARGET = tst_cannytest
CONFIG   += console c++14
CONFIG   -= app_bundle

QT       += testlib
TEMPLATE = app


SOURCES += \
    tst_image_iterator.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

unix|win32: LIBS += -L$$OUT_PWD/../src/common/ -lcommon

INCLUDEPATH += $$PWD/../src/common
DEPENDPATH += $$PWD/../src/common
