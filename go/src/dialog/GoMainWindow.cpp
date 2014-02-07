#include <QCloseEvent>
#include <QFileInfo>
#include <QDesktopServices>
#include <QUrl>
#include <QDate>
#include "GoMainWindow.h"
#include "ui_gomainwindow.h"
#include "DialogAbout.h"
#include "GlobalConfig.h"
using namespace std;

GoMainWindow::GoMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GoMainWindow)
{
    ui->setupUi(this);
    this->_close = false;
    this->setGeometry(10, 10, 1024, 768);
    this->showMaximized();
    this->_messageController = new MessageController();
    this->initDock();
    this->initEditor();
    this->bindMessage(this->_messageController);
}

GoMainWindow::~GoMainWindow()
{
    delete ui;
}

void GoMainWindow::bindMessage(MessageController *controller)
{
    this->Messager::bindMessage(controller);
    controller->listen(MessageFactory::TYPE_MAINWINDOW_CLOSE, this);
    this->sendMessage(MessageFactory::produce(MessageFactory::TYPE_MAINWINDOW_OPEN));
}

void GoMainWindow::messageEvent(shared_ptr<Message> message)
{
    switch (message->type())
    {
    case MessageFactory::TYPE_MAINWINDOW_CLOSE:
        this->_close =true;
        this->close();
        break;
    }
}

void GoMainWindow::closeEvent(QCloseEvent *event)
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

void GoMainWindow::initEditor()
{
    this->_dockToolbox = new DockToolbox(this);
    this->_dockToolbox->bindMessage(this->_messageController);
    this->_dockToolbox->setMaximumWidth(200);
    this->_dockToolbox->setFeatures(0);
    this->ui->widget->layout()->addWidget(this->_dockToolbox);

    this->_editor = new Editor(this);
    this->ui->widget->layout()->addWidget(this->_editor);
    this->_editor->bindMessage(this->_messageController);

    this->_dockParameter = new DockParameter(this);
    this->_dockParameter->bindMessage(this->_messageController);
    this->_dockParameter->setMaximumWidth(250);
    this->_dockParameter->setFeatures(0);
    this->_dockParameter->setFloating(false);
    this->ui->widget->layout()->addWidget(this->_dockParameter);
}

void GoMainWindow::initDock()
{
    this->_dockMessage = new DockMessage(this);
    this->_dockMessage->bindMessage(this->_messageController);
    this->addDockWidget(Qt::BottomDockWidgetArea, this->_dockMessage);
}

void GoMainWindow::on_toolButtonNew_clicked()
{
    shared_ptr<Message> message = MessageFactory::produce(MessageFactory::TYPE_EDITOR_NEW);
    message->paramInt = EditorFactory::EDITOR_TYPE_GO;
    this->sendMessage(message);
}

void GoMainWindow::on_toolButtonMarkov_clicked()
{
    shared_ptr<Message> message = MessageFactory::produce(MessageFactory::TYPE_EDITOR_NEW);
    message->paramInt = EditorFactory::EDITOR_TYPE_GO_MARKOV;
    this->sendMessage(message);
}

void GoMainWindow::on_toolButtonOpen_clicked()
{
    this->sendMessage(MessageFactory::produce(MessageFactory::TYPE_EDITOR_OPEN));
}

void GoMainWindow::on_toolButtonClose_clicked()
{
    this->sendMessage(MessageFactory::produce(MessageFactory::TYPE_EDITOR_CLOSE));
}

void GoMainWindow::on_toolButtonSave_clicked()
{
    this->sendMessage(MessageFactory::produce(MessageFactory::TYPE_EDITOR_SAVE));
}

void GoMainWindow::on_toolButtonSaveAs_clicked()
{
    this->sendMessage(MessageFactory::produce(MessageFactory::TYPE_EDITOR_SAVEAS));
}

void GoMainWindow::on_toolButtonSaveAll_clicked()
{
    this->sendMessage(MessageFactory::produce(MessageFactory::TYPE_EDITOR_SAVEALL));
}

void GoMainWindow::on_toolButtonAnalysis_clicked()
{
    this->sendMessage(MessageFactory::produce(MessageFactory::TYPE_EDITOR_ANALYSIS_PROBABILITY));
}

void GoMainWindow::on_toolButtonPath_clicked()
{
    this->sendMessage(MessageFactory::produce(MessageFactory::TYPE_EDITOR_ANALYSIS_PATH));
}

void GoMainWindow::on_toolButtonCut_clicked()
{
    this->sendMessage(MessageFactory::produce(MessageFactory::TYPE_EDITOR_ANALYSIS_CUT));
}

void GoMainWindow::on_toolButtonCopy_clicked()
{
    this->sendMessage(MessageFactory::produce(MessageFactory::TYPE_EDITOR_COPY));
}

void GoMainWindow::on_toolButtonDelete_clicked()
{
    this->sendMessage(MessageFactory::produce(MessageFactory::TYPE_EDITOR_DELETE));
}

void GoMainWindow::on_toolButtonZoomIn_clicked()
{
    this->sendMessage(MessageFactory::produce(MessageFactory::TYPE_EDITOR_ZOOM_IN));
}

void GoMainWindow::on_toolButtonZoomOut_clicked()
{
    this->sendMessage(MessageFactory::produce(MessageFactory::TYPE_EDITOR_ZOOM_OUT));
}

void GoMainWindow::on_toolButtonFeedback_clicked()
{
    this->sendMessage(MessageFactory::produce(MessageFactory::TYPE_EDITOR_SET_GLOBAL_FEEDBACK));
}

void GoMainWindow::on_toolButtonUnlockFb_clicked()
{
    this->sendMessage(MessageFactory::produce(MessageFactory::TYPE_EDITOR_UNSET_GLOBAL_FEEDBBACK));
}
