#-------------------------------------------------
#
# Project created by QtCreator 2013-03-13T08:46:31
#
#-------------------------------------------------

QT       += core gui

TARGET = ZGO2
TEMPLATE = app

INCLUDEPATH += ./include

TRANSLATIONS += lang/Lang_CH.ts

SOURCES += \
    src/main.cpp \
    src/view/mainwindow.cpp \
    src/view/editor.cpp \
    src/view/editorgo.cpp \
    src/view/editorabstract.cpp \
    src/view/editorwelcome.cpp \
    src/view/editorfactory.cpp \
    src/model/factoryabstract.cpp \
    src/view/scenego.cpp \
    src/view/viewgo.cpp \
    src/view/graphicsview.cpp

HEADERS += \
    include/view/mainwindow.h \
    include/view/editor.h \
    include/view/editorgo.h \
    include/view/editorabstract.h \
    include/view/editorwelcome.h \
    include/view/editorfactory.h \
    include/model/factoryabstract.h \
    include/view/scenego.h \
    include/view/viewgo.h \
    include/view/graphicsview.h

