#-------------------------------------------------
#
# Project created by QtCreator 2013-03-13T08:46:31
#
#-------------------------------------------------

QT       += core gui

TARGET = ZGO2
TEMPLATE = app

INCLUDEPATH += ./include
INCLUDEPATH += ./include/controller/defination
INCLUDEPATH += ./include/controller//message/control
INCLUDEPATH += ./include/controller//message/factory
INCLUDEPATH += ./include/controller//message/message
INCLUDEPATH += ./include/model/common
INCLUDEPATH += ./include/model/go
INCLUDEPATH += ./include/view/graphics/common
INCLUDEPATH += ./include/view/graphics/go
INCLUDEPATH += ./include/view/main/dock/message
INCLUDEPATH += ./include/view/main/dock/toolbox
INCLUDEPATH += ./include/view/main/editor
INCLUDEPATH += ./include/view/main/main
INCLUDEPATH += ./include/view/main/menu

TRANSLATIONS += lang/Lang_CH.ts

HEADERS += \
    include/controller/defination/definationtooltype.h \
    include/controller/defination/definationtoolboxtype.h \
    include/controller/defination/definationeditortype.h \
    include/controller/defination/definationeditorselectiontype.h \
    include/controller/message/control/messager.h \
    include/controller/message/control/messagelistener.h \
    include/controller/message/control/messagecreator.h \
    include/controller/message/control/messagecontroller.h \
    include/controller/message/factory/messagefactorymainwindow.h \
    include/controller/message/factory/messagefactoryeditor.h \
    include/controller/message/factory/messagefactory.h \
    include/controller/message/message/messagemainwindowtryclose.h \
    include/controller/message/message/messagemainwindowopen.h \
    include/controller/message/message/messagemainwindowclose.h \
    include/controller/message/message/messageeditortype.h \
    include/controller/message/message/messageeditorselection.h \
    include/controller/message/message/message.h \
    include/model/common/typeditem.h \
    include/model/common/nameditem.h \
    include/model/common/identifieditem.h \
    include/model/common/factoryabstract.h \
    include/model/go/gosignal.h \
    include/model/go/gooperator.h \
    include/model/go/goiomodel.h \
    include/view/graphics/common/itemmoveable.h \
    include/view/graphics/common/itemdrawable.h \
    include/view/graphics/common/itemarrow.h \
    include/view/graphics/common/graphicsview.h \
    include/view/graphics/go/viewgo.h \
    include/view/graphics/go/scenego.h \
    include/view/graphics/go/itemgosource.h \
    include/view/graphics/go/itemgooperator.h \
    include/view/main/dock/message/debugconsole.h \
    include/view/main/dock/message/dockmessage.h \
    include/view/main/dock/toolbox/toolboxabstract.h \
    include/view/main/dock/toolbox/docktoolbox.h \
    include/view/main/editor/editorwelcome.h \
    include/view/main/editor/editorgo.h \
    include/view/main/editor/editorfactory.h \
    include/view/main/editor/editorabstract.h \
    include/view/main/editor/editor.h \
    include/view/main/main/mainwindow.h \
    include/view/main/menu/mainmenu.h \
    include/view/main/dock/toolbox/toolboxfactory.h \
    include/view/main/dock/toolbox/toolboxnull.h \
    include/view/main/dock/toolbox/toolboxgo.h \
    include/controller/message/factory/messagefactorytool.h \
    include/controller/message/message/messagetoolselection.h

SOURCES += \
    src/controller/defination/definationtooltype.cpp \
    src/controller/defination/definationtoolboxtype.cpp \
    src/controller/defination/definationeditortype.cpp \
    src/controller/defination/definationeditorselectiontype.cpp \
    src/controller/message/control/messager.cpp \
    src/controller/message/control/messagelistener.cpp \
    src/controller/message/control/messagecreator.cpp \
    src/controller/message/control/messagecontroller.cpp \
    src/controller/message/factory/messagefactorymainwindow.cpp \
    src/controller/message/factory/messagefactoryeditor.cpp \
    src/controller/message/factory/messagefactory.cpp \
    src/controller/message/message/messagemainwindowtryclose.cpp \
    src/controller/message/message/messagemainwindowopen.cpp \
    src/controller/message/message/messagemainwindowclose.cpp \
    src/controller/message/message/messageeditortype.cpp \
    src/controller/message/message/messageeditorselection.cpp \
    src/controller/message/message/message.cpp \
    src/model/common/typeditem.cpp \
    src/model/common/nameditem.cpp \
    src/model/common/identifieditem.cpp \
    src/model/common/factoryabstract.cpp \
    src/model/go/gosignal.cpp \
    src/model/go/gooperator.cpp \
    src/model/go/goiomodel.cpp \
    src/view/graphics/common/itemmoveable.cpp \
    src/view/graphics/common/itemdrawable.cpp \
    src/view/graphics/common/itemarrow.cpp \
    src/view/graphics/common/graphicsview.cpp \
    src/view/graphics/go/viewgo.cpp \
    src/view/graphics/go/scenego.cpp \
    src/view/graphics/go/itemgosource.cpp \
    src/view/graphics/go/itemgooperator.cpp \
    src/view/main/dock/message/debugconsole.cpp \
    src/view/main/dock/message/dockmessage.cpp \
    src/view/main/dock/toolbox/toolboxabstract.cpp \
    src/view/main/dock/toolbox/docktoolbox.cpp \
    src/view/main/editor/editorwelcome.cpp \
    src/view/main/editor/editorgo.cpp \
    src/view/main/editor/editorfactory.cpp \
    src/view/main/editor/editorabstract.cpp \
    src/view/main/editor/editor.cpp \
    src/view/main/main/mainwindow.cpp \
    src/view/main/menu/mainmenu.cpp \
    src/main.cpp \
    src/view/main/dock/toolbox/toolboxfactory.cpp \
    src/view/main/dock/toolbox/toolboxnull.cpp \
    src/view/main/dock/toolbox/toolboxgo.cpp \
    src/controller/message/factory/messagefactorytool.cpp \
    src/controller/message/message/messagetoolselection.cpp

FORMS += \
    test.ui
