#include <QCloseEvent>
#include <QFileInfo>
#include <QDesktopServices>
#include <QUrl>
#include <QDate>
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
    this->setGeometry(100, 100, 1024, 768);
    this->showMaximized();
    this->_messageController = new MessageController();
    this->initDock();
    this->initEditor();
    this->bindMessage(this->_messageController);
}

GOMainWindow::~GOMainWindow()
{
    delete ui;
}

void GOMainWindow::bindMessage(MessageController *controller)
{
    this->Messager::bindMessage(controller);
    controller->listen(MessageFactory::TYPE_MAINWINDOW_CLOSE, this);
    this->sendMessage(MessageFactory::produce(MessageFactory::TYPE_MAINWINDOW_OPEN));
}

void GOMainWindow::messageEvent(QSharedPointer<Message> message)
{
    switch (message->type())
    {
    case MessageFactory::TYPE_MAINWINDOW_CLOSE:
        this->_close =true;
        this->close();
        break;
    }
}

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

void GOMainWindow::initEditor()
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

void GOMainWindow::initDock()
{
    this->_dockMessage = new DockMessage(this);
    this->_dockMessage->bindMessage(this->_messageController);
    this->addDockWidget(Qt::BottomDockWidgetArea, this->_dockMessage);
}

void GOMainWindow::on_toolButtonNew_clicked()
{
    QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_EDITOR_NEW);
    message->paramInt = EditorFactory::EDITOR_TYPE_GO;
    this->sendMessage(message);
}

void GOMainWindow::on_toolButtonMarkov_clicked()
{
    QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_EDITOR_NEW);
    message->paramInt = EditorFactory::EDITOR_TYPE_GO_MARKOV;
    this->sendMessage(message);
}

void GOMainWindow::on_toolButtonOpen_clicked()
{
    this->sendMessage(MessageFactory::produce(MessageFactory::TYPE_EDITOR_OPEN));
}

void GOMainWindow::on_toolButtonClose_clicked()
{
    this->sendMessage(MessageFactory::produce(MessageFactory::TYPE_EDITOR_CLOSE));
}

void GOMainWindow::on_toolButtonSave_clicked()
{
    this->sendMessage(MessageFactory::produce(MessageFactory::TYPE_EDITOR_SAVE));
}

void GOMainWindow::on_toolButtonSaveAs_clicked()
{
    this->sendMessage(MessageFactory::produce(MessageFactory::TYPE_EDITOR_SAVEAS));
}

void GOMainWindow::on_toolButtonSaveAll_clicked()
{
    this->sendMessage(MessageFactory::produce(MessageFactory::TYPE_EDITOR_SAVEALL));
}

void GOMainWindow::on_toolButtonAnalysis_clicked()
{
    this->sendMessage(MessageFactory::produce(MessageFactory::TYPE_EDITOR_ANALYSIS_PROBABILITY));
}

void GOMainWindow::on_toolButtonPath_clicked()
{
    this->sendMessage(MessageFactory::produce(MessageFactory::TYPE_EDITOR_ANALYSIS_PATH));
}

void GOMainWindow::on_toolButtonCut_clicked()
{
    this->sendMessage(MessageFactory::produce(MessageFactory::TYPE_EDITOR_ANALYSIS_CUT));
}

void GOMainWindow::on_toolButtonCopy_clicked()
{
    this->sendMessage(MessageFactory::produce(MessageFactory::TYPE_EDITOR_COPY));
}

void GOMainWindow::on_toolButtonDelete_clicked()
{
    this->sendMessage(MessageFactory::produce(MessageFactory::TYPE_EDITOR_DELETE));
}

void GOMainWindow::on_toolButtonZoomIn_clicked()
{
    this->sendMessage(MessageFactory::produce(MessageFactory::TYPE_EDITOR_ZOOM_IN));
}

void GOMainWindow::on_toolButtonZoomOut_clicked()
{
    this->sendMessage(MessageFactory::produce(MessageFactory::TYPE_EDITOR_ZOOM_OUT));
}

void GOMainWindow::on_toolButtonFeedback_clicked()
{
    this->sendMessage(MessageFactory::produce(MessageFactory::TYPE_EDITOR_SET_GLOBAL_FEEDBACK));
}

void GOMainWindow::on_toolButtonUnlockFb_clicked()
{
    this->sendMessage(MessageFactory::produce(MessageFactory::TYPE_EDITOR_UNSET_GLOBAL_FEEDBBACK));
}
