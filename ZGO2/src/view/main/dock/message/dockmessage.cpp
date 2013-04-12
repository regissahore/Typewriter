#include "dockmessage.h"

/**
 * 初始化窗体。
 */
DockMessage::DockMessage(QWidget *parent) : QDockWidget(parent), Messager()
{
    this->setWindowTitle(tr("Message"));
    this->setFeatures(QDockWidget::AllDockWidgetFeatures);
    QTabWidget *tabWidget = new QTabWidget(this);
    // 添加调试窗口。
    this->_debugConsole = new DebugConsole();
    tabWidget->addTab(this->_debugConsole, tr("Debug"));
    this->setWidget(tabWidget);
}

/**
 * 绑定消息。
 * @param controller 消息控制器。
 */
void DockMessage::bindMessage(MessageController *controller)
{
    this->_debugConsole->bindMessage(controller);
}
