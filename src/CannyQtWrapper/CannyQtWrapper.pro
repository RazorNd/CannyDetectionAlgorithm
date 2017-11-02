#-------------------------------------------------
#
# Project created by QtCreator 2016-10-16T18:01:12
#
#-------------------------------------------------

TARGET = CannyQtWrapper
TEMPLATE = lib

CONFIG += shared

DEFINES += CANNYQTWRAPPER_LIBRARY

SOURCES += \
    CannyDetectionAlgorithm.cpp

HEADERS +=\
        cannyqtwrapper_global.h \
    CannyDetectionAlgorithm.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../common/release/ -lcommon
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../common/debug/ -lcommon
else:unix: LIBS += -L$$OUT_PWD/../common/ -lcommon

INCLUDEPATH += $$PWD/../common
DEPENDPATH += $$PWD/../common
