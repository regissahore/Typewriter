#-------------------------------------------------
#
# Project created by QtCreator 2013-03-13T08:46:31
#
#-------------------------------------------------

QT      += core gui
QT      += xml
QT      += webkit

QT      += widgets
QT      += webkitwidgets

TARGET = go
TEMPLATE = app

RC_FILE = resource.rc

QMAKE_CXXFLAGS += -std=c++0x
QMAKE_LFLAGS = -static

INCLUDEPATH += ./include
INCLUDEPATH += ./include/analysis
INCLUDEPATH += ./include/analysis/origin
INCLUDEPATH += ./include/analysis/markov
INCLUDEPATH += ./include/define
INCLUDEPATH += ./include/dialog
INCLUDEPATH += ./include/editor
INCLUDEPATH += ./include/message
INCLUDEPATH += ./include/parameter
INCLUDEPATH += ./include/tool
INCLUDEPATH += ./include/view

TRANSLATIONS += lang/Lang_CH.ts

RESOURCES += \
    resource.qrc

FORMS += \
    form/DialogGoMarkovPeriod.ui \
    form/GoMainWindow.ui \
    form/DialogAbout.ui \
    form/ToolboxGo.ui \
    form/ToolboxGoMarkov.ui \
    form/DialogMatrixInput.ui \
    form/OutputConsole.ui \
    form/DialogGoMarkovAnalysisProcess.ui

HEADERS += \
    include/analysis/markov/DoubleVector.h \
    include/analysis/markov/GoMarkovAnalysis.h \
    include/analysis/markov/GoMarkovAnalysisThread.h \
    include/analysis/markov/GoMarkovChartData.h \
    include/analysis/markov/GoMarkovCommonCause.h \
    include/analysis/markov/GoMarkovEquivalent.h \
    include/analysis/markov/GoMarkovEquivalentParallel.h \
    include/analysis/markov/GoMarkovEquivalentSeries.h \
    include/analysis/markov/GoMarkovGraph.h \
    include/analysis/markov/GoMarkovOperator.h \
    include/analysis/markov/GoMarkovOperator1.h \
    include/analysis/markov/GoMarkovOperator10.h \
    include/analysis/markov/GoMarkovOperator11.h \
    include/analysis/markov/GoMarkovOperator11a.h \
    include/analysis/markov/GoMarkovOperator12.h \
    include/analysis/markov/GoMarkovOperator12a.h \
    include/analysis/markov/GoMarkovOperator13.h \
    include/analysis/markov/GoMarkovOperator13a.h \
    include/analysis/markov/GoMarkovOperator13b.h \
    include/analysis/markov/GoMarkovOperator14.h \
    include/analysis/markov/GoMarkovOperator15.h \
    include/analysis/markov/GoMarkovOperator15a.h \
    include/analysis/markov/GoMarkovOperator15b.h \
    include/analysis/markov/GoMarkovOperator16.h \
    include/analysis/markov/GoMarkovOperator17.h \
    include/analysis/markov/GoMarkovOperator18.h \
    include/analysis/markov/GoMarkovOperator18a.h \
    include/analysis/markov/GoMarkovOperator19.h \
    include/analysis/markov/GoMarkovOperator2.h \
    include/analysis/markov/GoMarkovOperator20.h \
    include/analysis/markov/GoMarkovOperator21.h \
    include/analysis/markov/GoMarkovOperator22.h \
    include/analysis/markov/GoMarkovOperator22a.h \
    include/analysis/markov/GoMarkovOperator22b.h \
    include/analysis/markov/GoMarkovOperator23.h \
    include/analysis/markov/GoMarkovOperator3.h \
    include/analysis/markov/GoMarkovOperator4.h \
    include/analysis/markov/GoMarkovOperator5.h \
    include/analysis/markov/GoMarkovOperator6.h \
    include/analysis/markov/GoMarkovOperator7.h \
    include/analysis/markov/GoMarkovOperator8.h \
    include/analysis/markov/GoMarkovOperator9.h \
    include/analysis/markov/GoMarkovOperator9a.h \
    include/analysis/markov/GoMarkovOperator9a1.h \
    include/analysis/markov/GoMarkovOperator9a2.h \
    include/analysis/markov/GoMarkovOperator9b.h \
    include/analysis/markov/GoMarkovOperator9b1.h \
    include/analysis/markov/GoMarkovOperator9b2.h \
    include/analysis/markov/GoMarkovOperatorFactory.h \
    include/analysis/markov/GoMarkovOperatorSplitPoint.h \
    include/analysis/markov/GoMarkovStatus.h \
    include/analysis/markov/RungeKuttaBreakdown3.h \
    include/analysis/markov/RungeKuttaBreakdown4.h \
    include/analysis/markov/RungeKuttaMarkov18.h \
    include/analysis/markov/RungeKuttaMarkov9a1.h \
    include/analysis/origin/GoAccumulative.h \
    include/analysis/origin/GoAnalysis.h \
    include/analysis/origin/GoCutSet.h \
    include/analysis/origin/GoGraph.h \
    include/analysis/origin/GoInput.h \
    include/analysis/origin/GoOperator.h \
    include/analysis/origin/GoOperatorFactory.h \
    include/analysis/origin/GoOutput.h \
    include/analysis/origin/GoParameter.h \
    include/analysis/origin/GoPathSet.h \
    include/analysis/origin/GoPathSetSet.h \
    include/analysis/origin/GoPathSetSetSet.h \
    include/analysis/origin/GoSignal.h \
    include/analysis/origin/GoSignalFactory.h \
    include/analysis/origin/GoStatus.h \
    include/define/DefinationEditorSelectionType.h \
    include/define/DefinationGoType.h \
    include/define/DefinationToolType.h \
    include/define/DomItem.h \
    include/define/FactoryAbstract.h \
    include/define/GlobalConfig.h \
    include/define/IdentifiedItem.h \
    include/define/NamedItem.h \
    include/define/TypedItem.h \
    include/dialog/DialogAbout.h \
    include/dialog/DialogGoMarkovAnalysisProcess.h \
    include/dialog/DialogGoMarkovPeriod.h \
    include/dialog/DialogGoProbability.h \
    include/dialog/DialogIntegerInput.h \
    include/dialog/DialogMatrixInput.h \
    include/dialog/DialogStringInput.h \
    include/dialog/GoMainWindow.h \
    include/editor/Editor.h \
    include/editor/EditorAbstract.h \
    include/editor/EditorFactory.h \
    include/editor/EditorGo.h \
    include/editor/EditorGoMarkov.h \
    include/editor/EditorGoMarkovChart.h \
    include/editor/EditorWebview.h \
    include/editor/EditorWelcome.h \
    include/message/DebugConsole.h \
    include/message/DockMessage.h \
    include/message/Message.h \
    include/message/MessageController.h \
    include/message/MessageCreator.h \
    include/message/MessageFactory.h \
    include/message/MessageListener.h \
    include/message/Messager.h \
    include/message/OutputConsole.h \
    include/parameter/DockParameter.h \
    include/parameter/ParameterAbstract.h \
    include/parameter/ParameterFactory.h \
    include/parameter/ParameterGoMarkovChart.h \
    include/parameter/ParameterGoMarkovCommonCause.h \
    include/parameter/ParameterGoMarkovEquivalent.h \
    include/parameter/ParameterGoMarkovOperator.h \
    include/parameter/ParameterGoOperator.h \
    include/parameter/ParameterGoSignal.h \
    include/parameter/ParameterGoText.h \
    include/tool/DockToolbox.h \
    include/tool/ToolboxAbstract.h \
    include/tool/ToolboxFactory.h \
    include/tool/ToolboxGo.h \
    include/tool/ToolboxGoMarkov.h \
    include/tool/ToolboxNull.h \
    include/tool/ToolGoAbstract.h \
    include/tool/ToolGoFactory.h \
    include/tool/ToolGoMarkovCommonCause.h \
    include/tool/ToolGoMarkovEquivalent.h \
    include/tool/ToolGoMarkovOperator.h \
    include/tool/ToolGoMarkovPointerExtend.h \
    include/tool/ToolGoMarkovText.h \
    include/tool/ToolGoOperator.h \
    include/tool/ToolGoPointerExtend.h \
    include/tool/ToolGoSelect.h \
    include/tool/ToolGoText.h \
    include/view/GraphicsView.h \
    include/view/ItemArrow.h \
    include/view/ItemDrawable.h \
    include/view/ItemEmpty.h \
    include/view/ItemGoFactory.h \
    include/view/ItemGoMarkovChart.h \
    include/view/ItemGoMarkovCommonCause.h \
    include/view/ItemGoMarkovEquivalent.h \
    include/view/ItemGoMarkovOperator.h \
    include/view/ItemGoOperator.h \
    include/view/ItemGoSignal.h \
    include/view/ItemGoText.h \
    include/view/ItemMoveable.h \
    include/view/ItemSelection.h \
    include/view/SceneGo.h \
    include/view/SceneGoMarkov.h \
    include/view/SceneGoMarkovChart.h \
    include/view/ViewGo.h \
    include/view/ViewGoMarkov.h \
    include/view/ViewGoMarkovChart.h \
    include/analysis/markov/RungeKutta.h \
    include/analysis/markov/RungeKuttaBreakdown2.h

SOURCES += \
    src/analysis/markov/DoubleVector.cpp \
    src/analysis/markov/GoMarkovAnalysis.cpp \
    src/analysis/markov/GoMarkovAnalysisThread.cpp \
    src/analysis/markov/GoMarkovChartData.cpp \
    src/analysis/markov/GoMarkovCommonCause.cpp \
    src/analysis/markov/GoMarkovEquivalent.cpp \
    src/analysis/markov/GoMarkovEquivalentParallel.cpp \
    src/analysis/markov/GoMarkovEquivalentSeries.cpp \
    src/analysis/markov/GoMarkovGraph.cpp \
    src/analysis/markov/GoMarkovOperator.cpp \
    src/analysis/markov/GoMarkovOperator1.cpp \
    src/analysis/markov/GoMarkovOperator10.cpp \
    src/analysis/markov/GoMarkovOperator11.cpp \
    src/analysis/markov/GoMarkovOperator11a.cpp \
    src/analysis/markov/GoMarkovOperator12.cpp \
    src/analysis/markov/GoMarkovOperator12a.cpp \
    src/analysis/markov/GoMarkovOperator13.cpp \
    src/analysis/markov/GoMarkovOperator13a.cpp \
    src/analysis/markov/GoMarkovOperator13b.cpp \
    src/analysis/markov/GoMarkovOperator14.cpp \
    src/analysis/markov/GoMarkovOperator15.cpp \
    src/analysis/markov/GoMarkovOperator15a.cpp \
    src/analysis/markov/GoMarkovOperator15b.cpp \
    src/analysis/markov/GoMarkovOperator16.cpp \
    src/analysis/markov/GoMarkovOperator17.cpp \
    src/analysis/markov/GoMarkovOperator18.cpp \
    src/analysis/markov/GoMarkovOperator18a.cpp \
    src/analysis/markov/GoMarkovOperator19.cpp \
    src/analysis/markov/GoMarkovOperator2.cpp \
    src/analysis/markov/GoMarkovOperator20.cpp \
    src/analysis/markov/GoMarkovOperator21.cpp \
    src/analysis/markov/GoMarkovOperator22.cpp \
    src/analysis/markov/GoMarkovOperator22a.cpp \
    src/analysis/markov/GoMarkovOperator22b.cpp \
    src/analysis/markov/GoMarkovOperator23.cpp \
    src/analysis/markov/GoMarkovOperator3.cpp \
    src/analysis/markov/GoMarkovOperator4.cpp \
    src/analysis/markov/GoMarkovOperator5.cpp \
    src/analysis/markov/GoMarkovOperator6.cpp \
    src/analysis/markov/GoMarkovOperator7.cpp \
    src/analysis/markov/GoMarkovOperator8.cpp \
    src/analysis/markov/GoMarkovOperator9.cpp \
    src/analysis/markov/GoMarkovOperator9a.cpp \
    src/analysis/markov/GoMarkovOperator9a1.cpp \
    src/analysis/markov/GoMarkovOperator9a2.cpp \
    src/analysis/markov/GoMarkovOperator9b.cpp \
    src/analysis/markov/GoMarkovOperator9b1.cpp \
    src/analysis/markov/GoMarkovOperator9b2.cpp \
    src/analysis/markov/GoMarkovOperatorFactory.cpp \
    src/analysis/markov/GoMarkovOperatorSplitPoint.cpp \
    src/analysis/markov/GoMarkovStatus.cpp \
    src/analysis/markov/RungeKuttaBreakdown3.cpp \
    src/analysis/markov/RungeKuttaBreakdown4.cpp \
    src/analysis/markov/RungeKuttaMarkov18.cpp \
    src/analysis/markov/RungeKuttaMarkov9a1.cpp \
    src/analysis/origin/GoAccumulative.cpp \
    src/analysis/origin/GoAnalysis.cpp \
    src/analysis/origin/GoCutSet.cpp \
    src/analysis/origin/GoGraph.cpp \
    src/analysis/origin/GoInput.cpp \
    src/analysis/origin/GoOperator.cpp \
    src/analysis/origin/GoOperatorFactory.cpp \
    src/analysis/origin/GoOutput.cpp \
    src/analysis/origin/GoParameter.cpp \
    src/analysis/origin/GoPathSet.cpp \
    src/analysis/origin/GoPathSetSet.cpp \
    src/analysis/origin/GoPathSetSetSet.cpp \
    src/analysis/origin/GoSignal.cpp \
    src/analysis/origin/GoSignalFactory.cpp \
    src/analysis/origin/GoStatus.cpp \
    src/define/FactoryAbstract.cpp \
    src/define/GlobalConfig.cpp \
    src/define/IdentifiedItem.cpp \
    src/define/NamedItem.cpp \
    src/define/TypedItem.cpp \
    src/dialog/DialogAbout.cpp \
    src/dialog/DialogGoMarkovAnalysisProcess.cpp \
    src/dialog/DialogGoMarkovPeriod.cpp \
    src/dialog/DialogGoProbability.cpp \
    src/dialog/DialogIntegerInput.cpp \
    src/dialog/DialogMatrixInput.cpp \
    src/dialog/DialogStringInput.cpp \
    src/dialog/GoMainWindow.cpp \
    src/editor/Editor.cpp \
    src/editor/EditorAbstract.cpp \
    src/editor/EditorFactory.cpp \
    src/editor/EditorGo.cpp \
    src/editor/EditorGoMarkov.cpp \
    src/editor/EditorGoMarkovChart.cpp \
    src/editor/EditorWebview.cpp \
    src/editor/EditorWelcome.cpp \
    src/main.cpp \
    src/message/DebugConsole.cpp \
    src/message/DockMessage.cpp \
    src/message/Message.cpp \
    src/message/MessageController.cpp \
    src/message/MessageCreator.cpp \
    src/message/MessageFactory.cpp \
    src/message/MessageListener.cpp \
    src/message/Messager.cpp \
    src/message/OutputConsole.cpp \
    src/parameter/DockParameter.cpp \
    src/parameter/ParameterAbstract.cpp \
    src/parameter/ParameterFactory.cpp \
    src/parameter/ParameterGoMarkovChart.cpp \
    src/parameter/ParameterGoMarkovCommonCause.cpp \
    src/parameter/ParameterGoMarkovEquivalent.cpp \
    src/parameter/ParameterGoMarkovOperator.cpp \
    src/parameter/ParameterGoOperator.cpp \
    src/parameter/ParameterGoSignal.cpp \
    src/parameter/ParameterGoText.cpp \
    src/tool/DockToolbox.cpp \
    src/tool/ToolboxAbstract.cpp \
    src/tool/ToolboxFactory.cpp \
    src/tool/ToolboxGo.cpp \
    src/tool/ToolboxGoMarkov.cpp \
    src/tool/ToolboxNull.cpp \
    src/tool/ToolGoAbstract.cpp \
    src/tool/ToolGoFactory.cpp \
    src/tool/ToolGoMarkovCommonCause.cpp \
    src/tool/ToolGoMarkovEquivalent.cpp \
    src/tool/ToolGoMarkovOperator.cpp \
    src/tool/ToolGoMarkovPointerExtend.cpp \
    src/tool/ToolGoMarkovText.cpp \
    src/tool/ToolGoOperator.cpp \
    src/tool/ToolGoPointerExtend.cpp \
    src/tool/ToolGoSelect.cpp \
    src/tool/ToolGoText.cpp \
    src/view/GraphicsView.cpp \
    src/view/ItemArrow.cpp \
    src/view/ItemDrawable.cpp \
    src/view/ItemEmpty.cpp \
    src/view/ItemGoFactory.cpp \
    src/view/ItemGoMarkovChart.cpp \
    src/view/ItemGoMarkovCommonCause.cpp \
    src/view/ItemGoMarkovEquivalent.cpp \
    src/view/ItemGoMarkovOperator.cpp \
    src/view/ItemGoOperator.cpp \
    src/view/ItemGoSignal.cpp \
    src/view/ItemGoText.cpp \
    src/view/ItemMoveable.cpp \
    src/view/ItemSelection.cpp \
    src/view/SceneGo.cpp \
    src/view/SceneGoMarkov.cpp \
    src/view/SceneGoMarkovChart.cpp \
    src/view/ViewGo.cpp \
    src/view/ViewGoMarkov.cpp \
    src/view/ViewGoMarkovChart.cpp \
    src/analysis/markov/RungeKutta.cpp \
    src/analysis/markov/RungeKuttaBreakdown2.cpp
