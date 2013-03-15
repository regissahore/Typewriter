#include "view/dockmessage.h"

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
    /*QGridLayout *debugConsoleLayout = new QGridLayout();
    debugConsoleLayout->setMargin(0);
    debugConsoleLayout->setSpacing(0);
    debugConsoleLayout->addWidget(this->_debugConsole);*/
    tabWidget->addTab(this->_debugConsole, tr("Debug"));
    // 添加TabWidget到窗体。
    /*QGridLayout *tabLayout = new QGridLayout(this);
    tabLayout->setMargin(0);
    tabLayout->setSpacing(0);
    tabLayout->addWidget(tabWidget);*/
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
