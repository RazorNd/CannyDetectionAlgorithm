#-------------------------------------------------
#
# Project created by QtCreator 2016-09-11T00:04:39
#
#-------------------------------------------------

TARGET = common
TEMPLATE = lib

DEFINES += COMMON_LIBRARY

SOURCES += CannyDetection.cpp

HEADERS += CannyDetection.h\
        common_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
