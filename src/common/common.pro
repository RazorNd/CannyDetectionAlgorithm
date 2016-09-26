#-------------------------------------------------
#
# Project created by QtCreator 2016-09-11T00:04:39
#
#-------------------------------------------------

TARGET = common
TEMPLATE = lib
QT += concurrent
CONFIG += c++14

DEFINES += COMMON_LIBRARY

SOURCES += CannyDetection.cpp \
    ImagePixelIterator.cpp \

HEADERS += CannyDetection.h\
        common_global.h \
    ImagePixelIterator.h \
    RangeIterator.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
