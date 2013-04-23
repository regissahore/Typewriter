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
    this->initEditor();
    this->initToolBar();
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

void GOMainWindow::initToolBar()
{
    this->ui->toolBarFile->addAction(this->ui->actionNew);
    this->ui->toolBarFile->addAction(this->ui->actionOpen_O);
    this->ui->toolBarFile->addAction(this->ui->actionClose_C);
    this->ui->toolBarFile->addSeparator();
    this->ui->toolBarFile->addAction(this->ui->actionSave_S);
    this->ui->toolBarFile->addAction(this->ui->actionSave_As);
    this->ui->toolBarFile->addAction(this->ui->actionSave_All);

    this->ui->toolBarAnalysis->addAction(this->ui->actionAnalysis_Probability);
    this->ui->toolBarAnalysis->addAction(this->ui->actionFind_Path);
    this->ui->toolBarAnalysis->addAction(this->ui->actionFind_Cut);
}

void GOMainWindow::on_actionNew_triggered()
{
    Message *message = MessageFactory::produce(MessageFactory::TYPE_EDITOR_NEW);
    message->paramInt = EditorFactory::EDITOR_TYPE_GO;
    this->sendMessage(message);
}

void GOMainWindow::on_actionNew_Markov_triggered()
{
    Message *message = MessageFactory::produce(MessageFactory::TYPE_EDITOR_NEW);
    message->paramInt = EditorFactory::EDITOR_TYPE_GO_MARKOV;
    this->sendMessage(message);
}

void GOMainWindow::on_actionOpen_O_triggered()
{
    this->sendMessage(MessageFactory::produce(MessageFactory::TYPE_EDITOR_OPEN));
}

void GOMainWindow::on_actionClose_C_triggered()
{
    this->sendMessage(MessageFactory::produce(MessageFactory::TYPE_EDITOR_CLOSE));
}

void GOMainWindow::on_actionClose_All_triggered()
{
    this->sendMessage(MessageFactory::produce(MessageFactory::TYPE_EDITOR_CLOSEALL));
}

void GOMainWindow::on_actionSave_S_triggered()
{
    this->sendMessage(MessageFactory::produce(MessageFactory::TYPE_EDITOR_SAVE));
}

void GOMainWindow::on_actionSave_As_triggered()
{
    this->sendMessage(MessageFactory::produce(MessageFactory::TYPE_EDITOR_SAVEAS));
}

void GOMainWindow::on_actionSave_All_triggered()
{
    this->sendMessage(MessageFactory::produce(MessageFactory::TYPE_EDITOR_SAVEALL));
}

void GOMainWindow::on_actionQuit_Q_triggered()
{
    this->sendMessage(MessageFactory::produce(MessageFactory::TYPE_MAINWINDOW_TRYCLOSE));
}

void GOMainWindow::on_actionAnalysis_Probability_triggered()
{
    this->sendMessage(MessageFactory::produce(MessageFactory::TYPE_EDITOR_ANALYSIS_PROBABILITY));
}

void GOMainWindow::on_actionFind_Path_triggered()
{
    this->sendMessage(MessageFactory::produce(MessageFactory::TYPE_EDITOR_ANALYSIS_PATH));
}

void GOMainWindow::on_actionFind_Cut_triggered()
{
    this->sendMessage(MessageFactory::produce(MessageFactory::TYPE_EDITOR_ANALYSIS_CUT));
}

void GOMainWindow::on_actionChinese_Simplified_triggered()
{

}

void GOMainWindow::on_actionEnglish_triggered()
{

}

void GOMainWindow::on_actionAbout_triggered()
{

}

void GOMainWindow::on_actionHelp_triggered()
{

}
