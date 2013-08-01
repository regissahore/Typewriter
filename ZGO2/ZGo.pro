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

RC_FILE = resource.rc

INCLUDEPATH += ./include

TRANSLATIONS += lang/Lang_CH.ts

HEADERS += \
    include/definationtooltype.h \
    include/definationeditorselectiontype.h \
    include/messager.h \
    include/messagelistener.h \
    include/messagecreator.h \
    include/messagecontroller.h \
    include/message.h \
    include/typeditem.h \
    include/nameditem.h \
    include/identifieditem.h \
    include/factoryabstract.h \
    include/gosignal.h \
    include/gooperator.h \
    include/itemmoveable.h \
    include/itemdrawable.h \
    include/itemarrow.h \
    include/graphicsview.h \
    include/viewgo.h \
    include/scenego.h \
    include/itemgooperator.h \
    include/debugconsole.h \
    include/dockmessage.h \
    include/toolboxabstract.h \
    include/docktoolbox.h \
    include/editorwelcome.h \
    include/editorgo.h \
    include/editorfactory.h \
    include/editorabstract.h \
    include/editor.h \
    include/toolboxfactory.h \
    include/toolboxnull.h \
    include/toolgoabstract.h \
    include/toolgopointer.h \
    include/toolgofactory.h \
    include/toolgomove.h \
    include/toolgozoom.h \
    include/toolgoselect.h \
    include/itemselection.h \
    include/toolgooperator.h \
    include/gooperatorfactory.h \
    include/dialogintegerinput.h \
    include/definationgotype.h \
    include/itemgosignal.h \
    include/toolgosignal.h \
    include/itemgofactory.h \
    include/messagefactory.h \
    include/domitem.h \
    include/dialogstringinput.h \
    include/toolgotext.h \
    include/itemgotext.h \
    include/dockparameter.h \
    include/parameterabstract.h \
    include/parameterfactory.h \
    include/parametergotext.h \
    include/parametergosignal.h \
    include/parametergooperator.h \
    include/gostatus.h \
    include/gosignalfactory.h \
    include/gograph.h \
    include/goanalysis.h \
    include/dialoggoprobability.h \
    include/editorwebview.h \
    include/goaccumulative.h \
    include/goinput.h \
    include/gooutput.h \
    include/goparameter.h \
    include/editorgomarkov.h \
    include/gomarkovoperator.h \
    include/gomarkovstatus.h \
    include/gomarkovequivalent.h \
    include/gopathset.h \
    include/gocutset.h \
    include/gopathsetset.h \
    include/gopathsetsetset.h \
    include/toolgopointerextend.h \
    include/gomarkovequivalentseries.h \
    include/gomarkovequivalentparallel.h \
    include/parametergomarkovoperator.h \
    include/itemgomarkovoperator.h \
    include/toolgomarkovoperator.h \
    include/gomarkovoperatorfactory.h \
    include/viewgomarkov.h \
    include/scenegomarkov.h \
    include/gomarkovanalysis.h \
    include/gomarkovgraph.h \
    include/itemgomarkovequivalent.h \
    include/toolgomarkovequivalent.h \
    include/toolgomarkovpointerextend.h \
    include/parametergomarkovequivalent.h \
    include/dialoggomarkovperiod.h \
    include/gomarkovchartdata.h \
    include/itemgomarkovchart.h \
    include/viewgomarkovchart.h \
    include/scenegomarkovchart.h \
    include/editorgomarkovchart.h \
    include/gomainwindow.h \
    include/dialogabout.h \
    include/toolgomarkovtext.h \
    include/toolgomarkovcommoncause.h \
    include/itemgomarkovcommoncause.h \
    include/gomarkovcommoncause.h \
    include/toolboxgo.h \
    include/toolboxgomarkov.h \
    include/parametergomarkovcommoncause.h \
    include/dialogmatrixinput.h \
    include/gomarkovoperator1.h \
    include/gomarkovoperator2.h \
    include/gomarkovoperator3.h \
    include/gomarkovoperator4.h \
    include/gomarkovoperator5.h \
    include/gomarkovoperator6.h \
    include/gomarkovoperator7.h \
    include/gomarkovoperator8.h \
    include/gomarkovoperator9.h \
    include/gomarkovoperator9a.h \
    include/gomarkovoperator9a1.h \
    include/gomarkovoperator9a2.h \
    include/gomarkovoperator9b.h \
    include/gomarkovoperator10.h \
    include/gomarkovoperator11.h \
    include/gomarkovoperator12.h \
    include/gomarkovoperator13.h \
    include/gomarkovoperator14.h \
    include/gomarkovoperator15.h \
    include/gomarkovoperator15a.h \
    include/gomarkovoperator15b.h \
    include/gomarkovoperator16.h \
    include/gomarkovoperator17.h \
    include/gomarkovoperator18.h \
    include/gomarkovoperator18a.h \
    include/gomarkovoperator19.h \
    include/gomarkovoperator20.h \
    include/gomarkovoperator21.h \
    include/gomarkovoperator22.h \
    include/gomarkovoperator22a.h \
    include/gomarkovoperator22b.h \
    include/gomarkovoperator23.h \
    include/gomarkovoperator24.h \
    include/gomarkovoperator25.h \
    include/gomarkovoperator26.h \
    include/gomarkovoperator27.h \
    include/gomarkovoperator28.h \
    include/gomarkovoperator29.h \
    include/gomarkovoperator12a.h \
    include/gomarkovoperator13a.h \
    include/gomarkovoperator13b.h \
    include/outputconsole.h \
    include/rungekuttamarkov9a1.h \
    include/rungekuttamarkov18.h \
    include/rungekuttabreakdown3.h \
    include/rungekuttabreakdown4.h

SOURCES += \
    src/main.cpp \
    src/definationtooltype.cpp \
    src/definationeditorselectiontype.cpp \
    src/messager.cpp \
    src/messagelistener.cpp \
    src/messagecreator.cpp \
    src/messagecontroller.cpp \
    src/message.cpp \
    src/typeditem.cpp \
    src/nameditem.cpp \
    src/identifieditem.cpp \
    src/factoryabstract.cpp \
    src/gosignal.cpp \
    src/gooperator.cpp \
    src/itemmoveable.cpp \
    src/itemdrawable.cpp \
    src/itemarrow.cpp \
    src/graphicsview.cpp \
    src/viewgo.cpp \
    src/scenego.cpp \
    src/itemgooperator.cpp \
    src/debugconsole.cpp \
    src/dockmessage.cpp \
    src/toolboxabstract.cpp \
    src/docktoolbox.cpp \
    src/editorwelcome.cpp \
    src/editorgo.cpp \
    src/editorfactory.cpp \
    src/editorabstract.cpp \
    src/editor.cpp \
    src/toolboxfactory.cpp \
    src/toolboxnull.cpp \
    src/toolgoabstract.cpp \
    src/toolgopointer.cpp \
    src/toolgofactory.cpp \
    src/toolgomove.cpp \
    src/toolgozoom.cpp \
    src/toolgoselect.cpp \
    src/itemselection.cpp \
    src/toolgooperator.cpp \
    src/gooperatorfactory.cpp \
    src/dialogintegerinput.cpp \
    src/definationgotype.cpp \
    src/itemgosignal.cpp \
    src/toolgosignal.cpp \
    src/itemgofactory.cpp \
    src/messagefactory.cpp \
    src/domitem.cpp \
    src/dialogstringinput.cpp \
    src/toolgotext.cpp \
    src/itemgotext.cpp \
    src/dockparameter.cpp \
    src/parameterabstract.cpp \
    src/parameterfactory.cpp \
    src/parametergotext.cpp \
    src/parametergosignal.cpp \
    src/parametergooperator.cpp \
    src/gostatus.cpp \
    src/gosignalfactory.cpp \
    src/gograph.cpp \
    src/goanalysis.cpp \
    src/dialoggoprobability.cpp \
    src/editorwebview.cpp \
    src/goaccumulative.cpp \
    src/goinput.cpp \
    src/gooutput.cpp \
    src/goparameter.cpp \
    src/editorgomarkov.cpp \
    src/gomarkovoperator.cpp \
    src/gomarkovstatus.cpp \
    src/gomarkovequivalent.cpp \
    src/gopathset.cpp \
    src/gocutset.cpp \
    src/gopathsetset.cpp \
    src/gopathsetsetset.cpp \
    src/toolgopointerextend.cpp \
    src/gomarkovequivalentseries.cpp \
    src/gomarkovequivalentparallel.cpp \
    src/parametergomarkovoperator.cpp \
    src/itemgomarkovoperator.cpp \
    src/toolgomarkovoperator.cpp \
    src/gomarkovoperatorfactory.cpp \
    src/viewgomarkov.cpp \
    src/scenegomarkov.cpp \
    src/gomarkovanalysis.cpp \
    src/gomarkovgraph.cpp \
    src/itemgomarkovequivalent.cpp \
    src/toolgomarkovequivalent.cpp \
    src/toolgomarkovpointerextend.cpp \
    src/parametergomarkovequivalent.cpp \
    src/dialoggomarkovperiod.cpp \
    src/gomarkovchartdata.cpp \
    src/itemgomarkovchart.cpp \
    src/viewgomarkovchart.cpp \
    src/scenegomarkovchart.cpp \
    src/editorgomarkovchart.cpp \
    src/gomainwindow.cpp \
    src/dialogabout.cpp \
    src/toolgomarkovtext.cpp \
    src/toolgomarkovcommoncause.cpp \
    src/itemgomarkovcommoncause.cpp \
    src/gomarkovcommoncause.cpp \
    src/toolboxgo.cpp \
    src/toolboxgomarkov.cpp \
    src/parametergomarkovcommoncause.cpp \
    src/dialogmatrixinput.cpp \
    src/gomarkovoperator1.cpp \
    src/gomarkovoperator2.cpp \
    src/gomarkovoperator3.cpp \
    src/gomarkovoperator4.cpp \
    src/gomarkovoperator5.cpp \
    src/gomarkovoperator6.cpp \
    src/gomarkovoperator7.cpp \
    src/gomarkovoperator8.cpp \
    src/gomarkovoperator9.cpp \
    src/gomarkovoperator9a.cpp \
    src/gomarkovoperator9a1.cpp \
    src/gomarkovoperator9a2.cpp \
    src/gomarkovoperator9b.cpp \
    src/gomarkovoperator10.cpp \
    src/gomarkovoperator11.cpp \
    src/gomarkovoperator12.cpp \
    src/gomarkovoperator13.cpp \
    src/gomarkovoperator14.cpp \
    src/gomarkovoperator15.cpp \
    src/gomarkovoperator15a.cpp \
    src/gomarkovoperator15b.cpp \
    src/gomarkovoperator16.cpp \
    src/gomarkovoperator17.cpp \
    src/gomarkovoperator18.cpp \
    src/gomarkovoperator18a.cpp \
    src/gomarkovoperator19.cpp \
    src/gomarkovoperator20.cpp \
    src/gomarkovoperator21.cpp \
    src/gomarkovoperator22.cpp \
    src/gomarkovoperator22a.cpp \
    src/gomarkovoperator22b.cpp \
    src/gomarkovoperator23.cpp \
    src/gomarkovoperator24.cpp \
    src/gomarkovoperator25.cpp \
    src/gomarkovoperator26.cpp \
    src/gomarkovoperator27.cpp \
    src/gomarkovoperator28.cpp \
    src/gomarkovoperator29.cpp \
    src/gomarkovoperator12a.cpp \
    src/gomarkovoperator13a.cpp \
    src/gomarkovoperator13b.cpp \
    src/outputconsole.cpp \
    src/rungekuttamarkov9a1.cpp \
    src/rungekuttamarkov18.cpp \
    src/rungekuttabreakdown3.cpp \
    src/rungekuttabreakdown4.cpp

RESOURCES += \
    resource.qrc

FORMS += \
    form/dialoggomarkovperiod.ui \
    form/gomainwindow.ui \
    form/dialogabout.ui \
    form/toolboxgo.ui \
    form/toolboxgomarkov.ui \
    form/dialogmatrixinput.ui \
    form/outputconsole.ui
