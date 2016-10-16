#-------------------------------------------------
#
# Project created by QtCreator 2016-09-11T00:04:39
#
#-------------------------------------------------

TARGET = common
TEMPLATE = lib
QT = gui
CONFIG += c++14

DEFINES += COMMON_LIBRARY

SOURCES += CannyDetection.cpp \
    ImagePixelIterator.cpp \
    PixelsMatrix.cpp \
    SobelOperator.cpp \
    RobinsonOperator.cpp

HEADERS += CannyDetection.h\
        common_global.h \
    ImagePixelIterator.h \
    PixelsMatrix.h \
    util.h \
    SupressOperator.h \
    SobelOperator.h \
    RobinsonOperator.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
