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
INCLUDEPATH += ./include/view/dialog
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
    include/controller/message/message/messagetoolselection.h \
    include/view/graphics/go/toolgoabstract.h \
    include/view/graphics/go/toolgopointer.h \
    include/view/graphics/go/toolgofactory.h \
    include/view/graphics/go/toolgomove.h \
    include/view/graphics/go/toolgozoom.h \
    include/view/graphics/go/toolgoselect.h \
    include/view/graphics/common/itemselection.h \
    include/view/graphics/go/toolgooperator.h \
    include/view/graphics/go/toolgooperatortype1.h \
    include/view/graphics/go/itemgooperatortype1.h \
    include/model/go/gooperatorfactory.h \
    include/view/dialog/dialogintegerinput.h \
    include/view/graphics/go/toolgooperatorunfixedinput.h \
    include/view/graphics/go/itemgooperatortype2.h \
    include/view/graphics/go/toolgooperatortype2.h \
    include/view/graphics/go/toolgooperatorunfixedoutput.h \
    include/view/graphics/go/itemgooperatortype3.h \
    include/view/graphics/go/toolgooperatortype3.h \
    include/view/graphics/go/itemgooperatortype4.h \
    include/view/graphics/go/toolgooperatortype4.h \
    include/view/graphics/go/itemgooperatortype5.h \
    include/view/graphics/go/toolgooperatortype5.h \
    include/view/graphics/go/itemgooperatortype6.h \
    include/view/graphics/go/toolgooperatortype6.h \
    include/view/graphics/go/itemgooperatortype7.h \
    include/view/graphics/go/toolgooperatortype7.h \
    include/view/graphics/go/itemgooperatortype8.h \
    include/view/graphics/go/toolgooperatortype8.h \
    include/view/graphics/go/itemgooperatortype9.h \
    include/view/graphics/go/toolgooperatortype9.h \
    include/view/graphics/go/itemgooperatortype10.h \
    include/view/graphics/go/toolgooperatortype10.h \
    include/view/graphics/go/itemgooperatortype11.h \
    include/view/graphics/go/toolgooperatortype11.h \
    include/view/graphics/go/itemgooperatortype12.h \
    include/view/graphics/go/toolgooperatortype12.h \
    include/view/graphics/go/itemgooperatortype13.h \
    include/view/graphics/go/toolgooperatortype13.h \
    include/view/graphics/go/itemgooperatortype14.h \
    include/view/graphics/go/toolgooperatortype14.h \
    include/view/graphics/go/itemgooperatortype15.h \
    include/view/graphics/go/toolgooperatortype15.h \
    include/view/graphics/go/itemgooperatortype16.h \
    include/view/graphics/go/toolgooperatortype16.h \
    include/view/graphics/go/itemgooperatortype17.h \
    include/view/graphics/go/toolgooperatortype17.h \
    include/controller/defination/definationgotype.h \
    include/view/graphics/go/itemgosignal.h \
    include/view/graphics/go/toolgosignal.h \
    include/view/graphics/go/itemgofactory.h

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
    src/controller/message/message/messagetoolselection.cpp \
    src/view/graphics/go/toolgoabstract.cpp \
    src/view/graphics/go/toolgopointer.cpp \
    src/view/graphics/go/toolgofactory.cpp \
    src/view/graphics/go/toolgomove.cpp \
    src/view/graphics/go/toolgozoom.cpp \
    src/view/graphics/go/toolgoselect.cpp \
    src/view/graphics/common/itemselection.cpp \
    src/view/graphics/go/toolgooperator.cpp \
    src/view/graphics/go/toolgooperatortype1.cpp \
    src/view/graphics/go/itemgooperatortype1.cpp \
    src/model/go/gooperatorfactory.cpp \
    src/view/dialog/dialogintegerinput.cpp \
    src/view/graphics/go/toolgooperatorunfixedinput.cpp \
    src/view/graphics/go/itemgooperatortype2.cpp \
    src/view/graphics/go/toolgooperatortype2.cpp \
    src/view/graphics/go/toolgooperatorunfixedoutput.cpp \
    src/view/graphics/go/itemgooperatortype3.cpp \
    src/view/graphics/go/toolgooperatortype3.cpp \
    src/view/graphics/go/itemgooperatortype4.cpp \
    src/view/graphics/go/toolgooperatortype4.cpp \
    src/view/graphics/go/itemgooperatortype5.cpp \
    src/view/graphics/go/toolgooperatortype5.cpp \
    src/view/graphics/go/itemgooperatortype6.cpp \
    src/view/graphics/go/toolgooperatortype6.cpp \
    src/view/graphics/go/itemgooperatortype7.cpp \
    src/view/graphics/go/toolgooperatortype7.cpp \
    src/view/graphics/go/itemgooperatortype8.cpp \
    src/view/graphics/go/toolgooperatortype8.cpp \
    src/view/graphics/go/itemgooperatortype9.cpp \
    src/view/graphics/go/toolgooperatortype9.cpp \
    src/view/graphics/go/itemgooperatortype10.cpp \
    src/view/graphics/go/toolgooperatortype10.cpp \
    src/view/graphics/go/itemgooperatortype11.cpp \
    src/view/graphics/go/toolgooperatortype11.cpp \
    src/view/graphics/go/itemgooperatortype12.cpp \
    src/view/graphics/go/toolgooperatortype12.cpp \
    src/view/graphics/go/itemgooperatortype13.cpp \
    src/view/graphics/go/toolgooperatortype13.cpp \
    src/view/graphics/go/itemgooperatortype14.cpp \
    src/view/graphics/go/toolgooperatortype14.cpp \
    src/view/graphics/go/itemgooperatortype15.cpp \
    src/view/graphics/go/toolgooperatortype15.cpp \
    src/view/graphics/go/itemgooperatortype16.cpp \
    src/view/graphics/go/toolgooperatortype16.cpp \
    src/view/graphics/go/itemgooperatortype17.cpp \
    src/view/graphics/go/toolgooperatortype17.cpp \
    src/controller/defination/definationgotype.cpp \
    src/view/graphics/go/itemgosignal.cpp \
    src/view/graphics/go/toolgosignal.cpp \
    src/view/graphics/go/itemgofactory.cpp

FORMS += \
    test.ui
