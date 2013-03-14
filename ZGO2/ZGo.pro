#-------------------------------------------------
#
# Project created by QtCreator 2013-03-13T08:46:31
#
#-------------------------------------------------

QT       += core gui

TARGET = ZGo
TEMPLATE = app

INCLUDEPATH += ./include

TRANSLATIONS += lang/Lang_CH.ts

SOURCES += \
    src/main.cpp \
    src/view/mainwindow.cpp \
    src/view/editor.cpp \
    src/view/editorgo.cpp \
    src/view/editorabstract.cpp

HEADERS += \
    include/view/mainwindow.h \
    include/view/editor.h \
    include/view/editorgo.h \
    include/view/editorabstract.h

