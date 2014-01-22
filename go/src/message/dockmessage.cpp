#include "DockMessage.h"
#include "DebugConsole.h"
#include "OutputConsole.h"

//#define DEBUG

DockMessage::DockMessage(QWidget *parent) : QDockWidget(parent), Messager()
{
    this->setWindowTitle(tr("Message"));
    this->setFeatures(QDockWidget::AllDockWidgetFeatures);
    QTabWidget *tabWidget = new QTabWidget(this);

#ifdef DEBUG
    // 添加调试窗口。
    this->_debugConsole = new DebugConsole();
    tabWidget->addTab(this->_debugConsole, tr("Debug"));
#endif
    // 添加分析过程的输出窗口。
    this->_outputConsole = new OutputConsole(this);
    tabWidget->addTab(this->_outputConsole, tr("Output"));

    this->setWidget(tabWidget);
}

void DockMessage::bindMessage(MessageController *controller)
{
#ifdef DEBUG
    this->_debugConsole->bindMessage(controller);
#endif
    this->_outputConsole->bindMessage(controller);
}
