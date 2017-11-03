#-------------------------------------------------
#
# Project created by QtCreator 2016-09-11T00:06:53
#
#-------------------------------------------------


TARGET = tst_cannytest
CONFIG   += console c++14
CONFIG   -= app_bundle

QT       += testlib concurrent
TEMPLATE = app


SOURCES += \
    tst_image_iterator.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../src/common/release/ -lcommon
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../src/common/debug/ -lcommon
else:unix: LIBS += -L$$OUT_PWD/../../../src/common/ -lcommon

INCLUDEPATH += $$PWD/../../../src/common
DEPENDPATH += PWD/../../../src/common
