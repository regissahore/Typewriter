#include <QCloseEvent>
#include <QFileInfo>
#include <QDesktopServices>
#include <QUrl>
#include "gomainwindow.h"
#include "ui_gomainwindow.h"
#include "dialogabout.h"
#include "globalconfig.h"

GOMainWindow::GOMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GOMainWindow)
{
    ui->setupUi(this);
    this->_close = false;
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
    GlobalConfig::getInstance()->save();
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
    this->_dockMessage = new DockMessage(this);
    this->_dockMessage->bindMessage(this->_messageController);
    this->addDockWidget(Qt::BottomDockWidgetArea, this->_dockMessage);
    this->_dockToolbox = new DockToolbox(this);
    this->_dockToolbox->bindMessage(this->_messageController);
    this->addDockWidget(Qt::LeftDockWidgetArea, this->_dockToolbox);
    this->connect(this->_dockToolbox, SIGNAL(visibilityChanged(bool)), this, SLOT(on_actionTool_DockWidget_toggled(bool)));
    this->_dockParameter = new DockParameter(this);
    this->_dockParameter->bindMessage(this->_messageController);
    this->addDockWidget(Qt::RightDockWidgetArea, this->_dockParameter);
    this->connect(this->_dockParameter, SIGNAL(visibilityChanged(bool)), this, SLOT(on_actionParameter_DockWidget_toggled(bool)));
    GlobalConfig *config = GlobalConfig::getInstance();
    if (!config->isShowDockTool())
    {
        this->ui->actionTool_DockWidget->setChecked(false);
    }
    if (!config->isShowDockParameter())
    {
        this->ui->actionParameter_DockWidget->setChecked(false);
    }
    if (!config->isShowDockMessage())
    {
        this->ui->actionMessage_DockWidget->setChecked(false);
    }
}

void GOMainWindow::initToolBar()
{
    this->ui->toolBarFile->addAction(this->ui->actionNew);
    this->ui->toolBarFile->addAction(this->ui->actionNew_Markov);
    this->ui->toolBarFile->addAction(this->ui->actionOpen_O);
    this->ui->toolBarFile->addAction(this->ui->actionClose_C);
    this->ui->toolBarFile->addSeparator();
    this->ui->toolBarFile->addAction(this->ui->actionSave_S);
    this->ui->toolBarFile->addAction(this->ui->actionSave_As);
    this->ui->toolBarFile->addAction(this->ui->actionSave_All);

    this->ui->toolBarAnalysis->addAction(this->ui->actionAnalysis_Probability);
    this->ui->toolBarAnalysis->addAction(this->ui->actionFind_Path);
    this->ui->toolBarAnalysis->addAction(this->ui->actionFind_Cut);
    this->ui->toolBarAnalysis->addSeparator();
    this->ui->toolBarAnalysis->addAction((this->ui->actionCopy_C));
    this->ui->toolBarAnalysis->addAction((this->ui->actionDelete_D));
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

void GOMainWindow::on_actionAbout_triggered()
{
    DialogAbout dialog(this);
    dialog.exec();
}

void GOMainWindow::on_actionHelp_triggered()
{
    QFileInfo file("doc/help.pdf");
    QDesktopServices::openUrl(QUrl::fromLocalFile(file.absoluteFilePath()));
}

void GOMainWindow::on_actionTool_DockWidget_toggled(bool value)
{
    this->ui->actionTool_DockWidget->setChecked(value);
    this->_dockToolbox->setVisible(value);
    GlobalConfig::getInstance()->setIsShowDockTool(value);
}

void GOMainWindow::on_actionMessage_DockWidget_toggled(bool value)
{
    this->ui->actionMessage_DockWidget->setChecked(value);
    this->_dockMessage->setVisible(value);
    GlobalConfig::getInstance()->setIsShowDockMessage(value);
}

void GOMainWindow::on_actionParameter_DockWidget_toggled(bool value)
{
    this->ui->actionParameter_DockWidget->setChecked(value);
    this->_dockParameter->setVisible(value);
    GlobalConfig::getInstance()->setIsShowDockParameter(value);
}

void GOMainWindow::on_actionFile_Toolbar_toggled(bool value)
{
    this->ui->toolBarFile->setVisible(value);
}

void GOMainWindow::on_actionAnalysis_Toolbar_toggled(bool value)
{
    this->ui->toolBarAnalysis->setVisible(value);
}

void GOMainWindow::on_actionCopy_C_triggered()
{
    this->sendMessage(MessageFactory::produce(MessageFactory::TYPE_EDITOR_COPY));
}

void GOMainWindow::on_actionDelete_D_triggered()
{
    this->sendMessage(MessageFactory::produce(MessageFactory::TYPE_EDITOR_DELETE));
}

void GOMainWindow::on_actionZoom_In_triggered()
{
    this->sendMessage(MessageFactory::produce(MessageFactory::TYPE_EDITOR_ZOOM_IN));
}

void GOMainWindow::on_actionZoom_Out_triggered()
{
    this->sendMessage(MessageFactory::produce(MessageFactory::TYPE_EDITOR_ZOOM_OUT));
}
