#-------------------------------------------------
#
# Project created by QtCreator 2016-10-13T22:41:33
#
#-------------------------------------------------

QT       += core gui widgets

CONFIG += c++14

TARGET = Simple
TEMPLATE = app


SOURCES += main.cpp \
    CannyWidget.cpp

FORMS += \
    CannyWidget.ui

HEADERS += \
    CannyWidget.h


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../common/release/ -lcommon
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../common/debug/ -lcommon
else:unix: LIBS += -L$$OUT_PWD/../common/ -lcommon

INCLUDEPATH += $$PWD/../common
DEPENDPATH += $$PWD/../common

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../CannyQtWrapper/release/ -lCannyQtWrapper
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../CannyQtWrapper/debug/ -lCannyQtWrapper
else:unix: LIBS += -L$$OUT_PWD/../CannyQtWrapper/ -lCannyQtWrapper

INCLUDEPATH += $$PWD/../CannyQtWrapper
DEPENDPATH += $$PWD/../CannyQtWrapper
