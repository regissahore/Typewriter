#-------------------------------------------------
#
# Project created by QtCreator 2013-03-13T08:46:31
#
#-------------------------------------------------

QT      += core gui
QT      += xml
QT      += webkit

QT      += widgets
QT      += network
QT      += webkitwidgets

TARGET = ZGO2
TEMPLATE = app

INCLUDEPATH += ./include
INCLUDEPATH += ./include/controller/defination
INCLUDEPATH += ./include/controller//message/control
INCLUDEPATH += ./include/controller//message/message
INCLUDEPATH += ./include/model/common
INCLUDEPATH += ./include/model/go
INCLUDEPATH += ./include/model/markov
INCLUDEPATH += ./include/view/dialog
INCLUDEPATH += ./include/view/graphics/common
INCLUDEPATH += ./include/view/graphics/go
INCLUDEPATH += ./include/view/graphics/markov
INCLUDEPATH += ./include/view/main/dock/message
INCLUDEPATH += ./include/view/main/dock/parameter
INCLUDEPATH += ./include/view/main/dock/toolbox
INCLUDEPATH += ./include/view/main/editor
INCLUDEPATH += ./include/view/main/main
INCLUDEPATH += ./include/view/main/menu

TRANSLATIONS += lang/Lang_CH.ts

HEADERS += \
    include/controller/defination/definationtooltype.h \
    include/controller/defination/definationeditortype.h \
    include/controller/defination/definationeditorselectiontype.h \
    include/controller/message/control/messager.h \
    include/controller/message/control/messagelistener.h \
    include/controller/message/control/messagecreator.h \
    include/controller/message/control/messagecontroller.h \
    include/controller/message/message/message.h \
    include/model/common/typeditem.h \
    include/model/common/nameditem.h \
    include/model/common/identifieditem.h \
    include/model/common/factoryabstract.h \
    include/model/go/gosignal.h \
    include/model/go/gooperator.h \
    include/view/graphics/common/itemmoveable.h \
    include/view/graphics/common/itemdrawable.h \
    include/view/graphics/common/itemarrow.h \
    include/view/graphics/common/graphicsview.h \
    include/view/graphics/go/viewgo.h \
    include/view/graphics/go/scenego.h \
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
    include/view/graphics/go/toolgoabstract.h \
    include/view/graphics/go/toolgopointer.h \
    include/view/graphics/go/toolgofactory.h \
    include/view/graphics/go/toolgomove.h \
    include/view/graphics/go/toolgozoom.h \
    include/view/graphics/go/toolgoselect.h \
    include/view/graphics/common/itemselection.h \
    include/view/graphics/go/toolgooperator.h \
    include/model/go/gooperatorfactory.h \
    include/view/dialog/dialogintegerinput.h \
    include/controller/defination/definationgotype.h \
    include/view/graphics/go/itemgosignal.h \
    include/view/graphics/go/toolgosignal.h \
    include/view/graphics/go/itemgofactory.h \
    include/view/main/menu/mainmenuabstract.h \
    include/view/main/menu/mainmenufile.h \
    include/controller/message/message/messagefactory.h \
    include/model/common/domitem.h \
    include/view/dialog/dialogstringinput.h \
    include/view/graphics/go/toolgotext.h \
    include/view/graphics/go/itemgotext.h \
    include/view/main/dock/parameter/dockparameter.h \
    include/view/main/dock/parameter/parameterabstract.h \
    include/view/main/dock/parameter/parameterfactory.h \
    include/view/main/dock/parameter/delegatelineedit.h \
    include/view/main/dock/parameter/parametergotext.h \
    include/view/main/dock/parameter/tablewidgetgoitem.h \
    include/view/main/dock/parameter/parametergosignal.h \
    include/view/main/dock/parameter/parametergooperator.h \
    include/model/go/gostatus.h \
    include/model/go/gosignalfactory.h \
    include/model/go/gograph.h \
    include/model/go/goanalysis.h \
    include/view/main/dock/parameter/dialoggoprobability.h \
    include/view/main/menu/mainmenuanalysis.h \
    include/view/main/editor/editorwebview.h \
    include/model/go/goaccumulative.h \
    include/model/go/goinput.h \
    include/model/go/gooutput.h \
    include/model/common/biginteger.h \
    include/model/common/bigdecimal.h \
    include/model/go/goparameter.h \
    include/view/main/editor/editorgomarkov.h \
    include/model/markov/gomarkovoperator.h \
    include/model/markov/gomarkovstatus.h \
    include/model/markov/gomarkovequivalent.h \
    include/model/go/gopathset.h \
    include/model/go/gocutset.h \
    include/model/go/gopathsetset.h \
    include/model/go/gopathsetsetset.h \
    include/view/graphics/go/toolgopointerextend.h \
    include/model/markov/gomarkovequivalentseries.h \
    include/model/markov/gomarkovequivalentparallel.h \
    include/view/main/dock/toolbox/toolboxgomarkov.h \
    include/view/main/dock/parameter/parametergomarkovoperator.h \
    include/view/graphics/markov/itemgomarkovoperator.h \
    include/view/graphics/markov/toolgomarkovoperator.h \
    include/model/markov/gomarkovoperatorfactory.h \
    include/view/graphics/markov/viewgomarkov.h \
    include/view/graphics/markov/scenegomarkov.h \
    include/model/markov/gomarkovanalysis.h \
    include/model/markov/gomarkovgraph.h \
    include/view/graphics/markov/itemgomarkovequivalent.h \
    include/view/graphics/markov/toolgomarkovequivalent.h \
    include/view/graphics/markov/toolgomarkovpointerextend.h \
    include/view/main/dock/parameter/parametergomarkovequivalent.h

SOURCES += \
    src/controller/defination/definationtooltype.cpp \
    src/controller/defination/definationeditortype.cpp \
    src/controller/defination/definationeditorselectiontype.cpp \
    src/controller/message/control/messager.cpp \
    src/controller/message/control/messagelistener.cpp \
    src/controller/message/control/messagecreator.cpp \
    src/controller/message/control/messagecontroller.cpp \
    src/controller/message/message/message.cpp \
    src/model/common/typeditem.cpp \
    src/model/common/nameditem.cpp \
    src/model/common/identifieditem.cpp \
    src/model/common/factoryabstract.cpp \
    src/model/go/gosignal.cpp \
    src/model/go/gooperator.cpp \
    src/view/graphics/common/itemmoveable.cpp \
    src/view/graphics/common/itemdrawable.cpp \
    src/view/graphics/common/itemarrow.cpp \
    src/view/graphics/common/graphicsview.cpp \
    src/view/graphics/go/viewgo.cpp \
    src/view/graphics/go/scenego.cpp \
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
    src/view/graphics/go/toolgoabstract.cpp \
    src/view/graphics/go/toolgopointer.cpp \
    src/view/graphics/go/toolgofactory.cpp \
    src/view/graphics/go/toolgomove.cpp \
    src/view/graphics/go/toolgozoom.cpp \
    src/view/graphics/go/toolgoselect.cpp \
    src/view/graphics/common/itemselection.cpp \
    src/view/graphics/go/toolgooperator.cpp \
    src/model/go/gooperatorfactory.cpp \
    src/view/dialog/dialogintegerinput.cpp \
    src/controller/defination/definationgotype.cpp \
    src/view/graphics/go/itemgosignal.cpp \
    src/view/graphics/go/toolgosignal.cpp \
    src/view/graphics/go/itemgofactory.cpp \
    src/view/main/menu/mainmenuabstract.cpp \
    src/view/main/menu/mainmenufile.cpp \
    src/controller/message/message/messagefactory.cpp \
    src/model/common/domitem.cpp \
    src/view/dialog/dialogstringinput.cpp \
    src/view/graphics/go/toolgotext.cpp \
    src/view/graphics/go/itemgotext.cpp \
    src/view/main/dock/parameter/dockparameter.cpp \
    src/view/main/dock/parameter/parameterabstract.cpp \
    src/view/main/dock/parameter/parameterfactory.cpp \
    src/view/main/dock/parameter/delegatelineedit.cpp \
    src/view/main/dock/parameter/parametergotext.cpp \
    src/view/main/dock/parameter/tablewidgetgoitem.cpp \
    src/view/main/dock/parameter/parametergosignal.cpp \
    src/view/main/dock/parameter/parametergooperator.cpp \
    src/model/go/gostatus.cpp \
    src/model/go/gosignalfactory.cpp \
    src/model/go/gograph.cpp \
    src/model/go/goanalysis.cpp \
    src/view/main/dock/parameter/dialoggoprobability.cpp \
    src/view/main/menu/mainmenuanalysis.cpp \
    src/view/main/editor/editorwebview.cpp \
    src/model/go/goaccumulative.cpp \
    src/model/go/goinput.cpp \
    src/model/go/gooutput.cpp \
    src/model/common/biginteger.cpp \
    src/model/common/bigdecimal.cpp \
    src/model/go/goparameter.cpp \
    src/view/main/editor/editorgomarkov.cpp \
    src/model/markov/gomarkovoperator.cpp \
    src/model/markov/gomarkovstatus.cpp \
    src/model/markov/gomarkovequivalent.cpp \
    src/model/go/gopathset.cpp \
    src/model/go/gocutset.cpp \
    src/model/go/gopathsetset.cpp \
    src/model/go/gopathsetsetset.cpp \
    src/view/graphics/go/toolgopointerextend.cpp \
    src/model/markov/gomarkovequivalentseries.cpp \
    src/model/markov/gomarkovequivalentparallel.cpp \
    src/view/main/dock/toolbox/toolboxgomarkov.cpp \
    src/view/main/dock/parameter/parametergomarkovoperator.cpp \
    src/view/graphics/markov/itemgomarkovoperator.cpp \
    src/view/graphics/markov/toolgomarkovoperator.cpp \
    src/model/markov/gomarkovoperatorfactory.cpp \
    src/view/graphics/markov/viewgomarkov.cpp \
    src/view/graphics/markov/scenegomarkov.cpp \
    src/model/markov/gomarkovanalysis.cpp \
    src/model/markov/gomarkovgraph.cpp \
    src/view/graphics/markov/itemgomarkovequivalent.cpp \
    src/view/graphics/markov/toolgomarkovequivalent.cpp \
    src/view/graphics/markov/toolgomarkovpointerextend.cpp \
    src/view/main/dock/parameter/parametergomarkovequivalent.cpp
