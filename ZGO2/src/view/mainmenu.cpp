#include "view/mainmenu.h"

/**
 * 初始化菜单。
 */
MainMenu::MainMenu(QWidget *parent) : QMenuBar(parent), Messager()
{
    // 文件菜单。
    this->_menuFile = this->addMenu(tr("File(&F)"));
    this->_actionClose = this->_menuFile->addAction(tr("Close"));
    this->connect(this->_actionClose, SIGNAL(triggered()), this, SLOT(slotActionClose()));
    // 帮助菜单。
    this->_menuHelp = this->addMenu(tr("Help(&H)"));
}

/**
 * 绑定消息。
 * @param controller 控制器。
 */
void MainMenu::bindMessage(MessageController *controller)
{
    this->Messager::bindMessage(controller);
}

/**
 * 尝试关闭程序。
 */
void MainMenu::slotActionClose()
{
    MessageFactoryMainWindow factory;
    this->sendMessage(factory.produce(MessageFactoryMainWindow::MAINWINDOW_TRYCLOSE));
}
