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

SOURCES += src/main.cpp \
    src/VCMainWindow.cpp \
    src/MIGoOperator.cpp \
    src/MIGoSignal.cpp \
    src/MAGoOperator.cpp \
    src/MAGoSignal.cpp \
    src/MCGoOperatorFactory.cpp \
    src/VIGoDrawable.cpp \
    src/VIGoMoveable.cpp \
    src/VAGoUnit.cpp \
    src/VAGoLine.cpp \
    src/VIGoLine.cpp \
    src/VIGoUnit.cpp \
    src/VCDockProject.cpp \
    src/VCDockParameter.cpp \
    src/VCDockConsole.cpp \
    src/VCWidgetDrawing.cpp \
    src/VCDockTool.cpp \
    src/VCWidgetEditor.cpp

HEADERS  += \
    include/VCMainWindow.h \
    include/MIGoOperator.h \
    include/MIGoSignal.h \
    include/MAGoOperator.h \
    include/MAGoSignal.h \
    include/MCGoOperatorFactory.h \
    include/VIGoDrawable.h \
    include/VIGoMoveable.h \
    include/VAGoUnit.h \
    include/VAGoLine.h \
    include/VIGoLine.h \
    include/VIGoUnit.h \
    include/VCDockProject.h \
    include/VCDockParameter.h \
    include/VCDockConsole.h \
    include/VCWidgetDrawing.h \
    include/VCDockTool.h \
    include/VCWidgetEditor.h

FORMS    += \
    form/VCMainWindow.ui \
    form/VCDockProject.ui \
    form/VCDockParameter.ui \
    form/VCDockConsole.ui \
    form/VCWidgetDrawing.ui \
    form/VCDockTool.ui \
    form/VCWidgetEditor.ui
