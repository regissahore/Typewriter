#include "view/mainwindow.h"

/**
 * 构造函数，初始化界面。
 * @param parent 父窗体。
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), Messager()
{
    this->setWindowTitle(tr("ZHG GO Methodology"));
    this->setGeometry(100, 100, 800, 600);
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
}

/**
 * 为各个组成部分绑定消息。
 */
void MainWindow::bindMessage()
{
    this->_messageController = new MessageController();
    this->bindMessage(this->_messageController);
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
