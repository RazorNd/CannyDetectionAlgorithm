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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../src/CannyQtWrapper/release/ -lCannyQtWrapper
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../src/CannyQtWrapper/debug/ -lCannyQtWrapper
else:unix: LIBS += -L$$OUT_PWD/../src/CannyQtWrapper/ -lCannyQtWrapper

INCLUDEPATH += $$PWD/../src/CannyQtWrapper
DEPENDPATH += $$PWD/../src/CannyQtWrapper

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../src/common/release/ -lcommon
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../src/common/debug/ -lcommon
else:unix: LIBS += -L$$OUT_PWD/../src/common/ -lcommon

INCLUDEPATH += $$PWD/../src/common
DEPENDPATH += $$PWD/../src/common
