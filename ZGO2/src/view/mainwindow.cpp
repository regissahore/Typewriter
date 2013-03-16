#include "view/mainwindow.h"

/**
 * 构造函数，初始化界面。
 * @param parent 父窗体。
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), Messager()
{
    this->_close = false;
    this->setWindowTitle(tr("ZHG GO Methodology"));
    this->setGeometry(100, 100, 800, 600);
    this->initMenu();
    this->initEditor();
    this->initDock();
    this->bindMessage();
}

/**
 * 析构函数，清除界面资源。
 */
MainWindow::~MainWindow()
{
    this->clearDock();
    this->clearEditor();
    this->clearMenu();
}

/**
 * 为各个组成部分绑定消息。
 */
void MainWindow::bindMessage()
{
    this->_messageController = new MessageController();
    this->bindMessage(this->_messageController);
    this->_mainMenu->bindMessage(this->_messageController);
    this->_editor->bindMessage(this->_messageController);
    this->_dockMessage->bindMessage(this->_messageController);
    MessageFactoryMainWindow factory;
    this->sendMessage(factory.produce(MessageFactoryMainWindow::MAINWINDOW_OPEN));
}

/**
 * 绑定消息。
 * @param controller 消息控制器。
 */
void MainWindow::bindMessage(MessageController *controller)
{
    this->Messager::bindMessage(controller);
    MessageFactoryMainWindow factory;
    controller->listen(factory.getMessageName(MessageFactoryMainWindow::MAINWINDOW_CLOSE), this);
}

/**
 * 消息事件。
 * @param message 消息。
 */
void MainWindow::messageEvent(Message *message)
{
    MessageFactoryMainWindow factory;
    if (message->name() == factory.getMessageName(MessageFactoryMainWindow::MAINWINDOW_CLOSE))
    {
        this->_close = true;
        this->close();
    }
}

/**
 * 关闭事件。
 * @param event 关闭事件。
 */
void MainWindow::closeEvent(QCloseEvent *event)
{
    if (this->_close)
    {
        this->QMainWindow::closeEvent(event);
    }
    else
    {
        MessageFactoryMainWindow factory;
        this->sendMessage(factory.produce(MessageFactoryMainWindow::MAINWINDOW_TRYCLOSE));
        if (!this->_close)
        {
            event->ignore();
        }
    }
}

/**
 * 初始化编辑器。
 */
void MainWindow::initEditor()
{
    this->_editor = new Editor(this);
    this->setCentralWidget(this->_editor);
}

/**
 * 清除编辑器。
 * @return
 */
void MainWindow::clearEditor()
{
    if (this->_editor)
    {
        delete this->_editor;
        this->_editor = 0L;
    }
}

/**
 * 初始化悬停窗口。
 */
void MainWindow::initDock()
{
    this->_dockMessage = new DockMessage(this);
    this->addDockWidget(Qt::BottomDockWidgetArea, this->_dockMessage);
}

/**
 * 清除悬停窗口。
 */
void MainWindow::clearDock()
{
    if (this->_dockMessage)
    {
        delete this->_dockMessage;
        this->_dockMessage = 0L;
    }
}

/**
 * 初始化菜单。
 */
void MainWindow::initMenu()
{
    this->_mainMenu = new MainMenu();
    this->setMenuBar(this->_mainMenu);
}

/**
 * 清除菜单。
 */
void MainWindow::clearMenu()
{
    if (this->_mainMenu)
    {
        delete this->_mainMenu;
        this->_mainMenu = 0L;
    }
}
