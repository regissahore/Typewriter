#include <QCloseEvent>
#include "gomainwindow.h"
#include "ui_gomainwindow.h"

GOMainWindow::GOMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GOMainWindow)
{
    ui->setupUi(this);
    this->_close = false;
    this->setWindowTitle(tr("ZHG GO Methodology"));
    this->setGeometry(100, 100, 800, 600);
    this->_messageController = new MessageController();
    this->initDock();
    this->initMenu();
    this->initEditor();
    this->bindMessage(this->_messageController);
}

GOMainWindow::~GOMainWindow()
{
    delete ui;
}

/**
 * 绑定消息。
 * @param controller 消息控制器。
 */
void GOMainWindow::bindMessage(MessageController *controller)
{
    this->Messager::bindMessage(controller);
    controller->listen(MessageFactory::TYPE_MAINWINDOW_CLOSE, this);
    this->sendMessage(MessageFactory::produce(MessageFactory::TYPE_MAINWINDOW_OPEN));
}

/**
 * 消息事件。
 * @param message 消息。
 */
void GOMainWindow::messageEvent(Message *message)
{
    switch (message->type())
    {
    case MessageFactory::TYPE_MAINWINDOW_CLOSE:
        this->_close =true;
        this->close();
        break;
    }
}

/**
 * 关闭事件。
 * @param event 关闭事件。
 */
void GOMainWindow::closeEvent(QCloseEvent *event)
{
    if (this->_close)
    {
        this->QMainWindow::closeEvent(event);
    }
    else
    {
        this->sendMessage(MessageFactory::produce(MessageFactory::TYPE_MAINWINDOW_TRYCLOSE));
        if (!this->_close)
        {
            event->ignore();
        }
    }
}

/**
 * 初始化编辑器。
 */
void GOMainWindow::initEditor()
{
    this->_editor = new Editor(this);
    this->setCentralWidget(this->_editor);
    this->_editor->bindMessage(this->_messageController);
}

/**
 * 初始化悬停窗口。
 */
void GOMainWindow::initDock()
{
    //this->_dockMessage = new DockMessage(this);
    //this->_dockMessage->bindMessage(this->_messageController);
    //this->addDockWidget(Qt::BottomDockWidgetArea, this->_dockMessage);
    this->_dockToolbox = new DockToolbox(this);
    this->_dockToolbox->bindMessage(this->_messageController);
    this->addDockWidget(Qt::LeftDockWidgetArea, this->_dockToolbox);
    this->_dockParameter = new DockParameter(this);
    this->_dockParameter->bindMessage(this->_messageController);
    this->addDockWidget(Qt::RightDockWidgetArea, this->_dockParameter);
}

/**
 * 初始化菜单。
 */
void GOMainWindow::initMenu()
{
    this->_mainMenu = new MainMenu(this);
    this->setMenuBar(this->_mainMenu);
    this->_mainMenu->bindMessage(this->_messageController);
}
