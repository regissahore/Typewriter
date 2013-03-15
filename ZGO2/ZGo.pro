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
    src/view/graphicsview.cpp \
    src/view/itemdrawable.cpp \
    src/view/itemmoveable.cpp \
    src/view/itemgosource.cpp \
    src/model/identifieditem.cpp \
    src/model/gooperator.cpp \
    src/model/gosignal.cpp \
    src/model/goiomodel.cpp \
    src/model/nameditem.cpp \
    src/view/itemgooperator.cpp \
    src/view/itemarrow.cpp

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
    include/view/graphicsview.h \
    include/view/itemdrawable.h \
    include/view/itemmoveable.h \
    include/view/itemgosource.h \
    include/model/identifieditem.h \
    include/model/gooperator.h \
    include/model/gosignal.h \
    include/model/goiomodel.h \
    include/model/nameditem.h \
    include/view/itemgooperator.h \
    include/view/itemarrow.h

