#include <QCloseEvent>
#include <QFileInfo>
#include <QDesktopServices>
#include <QUrl>
#include <QDate>
#include "GoMainWindow.h"
#include "ui_GoMainWindow.h"
#include "DialogAbout.h"
#include "GlobalConfig.h"
using namespace std;

GoMainWindow::GoMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GoMainWindow),
    _editor(this),
    _dockMessage(this), _dockParameter(this), _dockToolbox(this)
{
    ui->setupUi(this);
    this->_close = false;
    this->setGeometry(10, 10, 1024, 768);
    this->showMaximized();
    this->initDock();
    this->initEditor();
    this->bindMessage();
}

GoMainWindow::~GoMainWindow()
{
    this->Messager::~Messager();
    delete ui;
}

void GoMainWindow::bindMessage()
{
    this->listen(MessageFactory::TYPE_MAINWINDOW_CLOSE);
    this->send(MessageFactory::produce(MessageFactory::TYPE_MAINWINDOW_OPEN));
}

void GoMainWindow::messageEvent(QSharedPointer<Message> message)
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
        this->send(MessageFactory::produce(MessageFactory::TYPE_MAINWINDOW_TRYCLOSE));
        if (!this->_close)
        {
            event->ignore();
        }
    }
}

void GoMainWindow::initEditor()
{
    this->_dockToolbox.bindMessage();
    this->_dockToolbox.setMaximumWidth(200);
    this->_dockToolbox.setFeatures(0);
    this->ui->widget->layout()->addWidget(&this->_dockToolbox);

    this->_editor.bindMessage();
    this->ui->widget->layout()->addWidget(&this->_editor);

    this->_dockParameter.bindMessage();
    this->_dockParameter.setMaximumWidth(250);
    this->_dockParameter.setFeatures(0);
    this->_dockParameter.setFloating(false);
    this->ui->widget->layout()->addWidget(&this->_dockParameter);
}

void GoMainWindow::initDock()
{
    this->_dockMessage.bindMessage();
    this->addDockWidget(Qt::BottomDockWidgetArea, &this->_dockMessage);
}

void GoMainWindow::on_toolButtonNew_clicked()
{
    QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_EDITOR_NEW);
    message->paramInt = EditorFactory::EDITOR_TYPE_GO;
    this->send(message);
}

void GoMainWindow::on_toolButtonMarkov_clicked()
{
    QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_EDITOR_NEW);
    message->paramInt = EditorFactory::EDITOR_TYPE_GO_MARKOV;
    this->send(message);
}

void GoMainWindow::on_toolButtonOpen_clicked()
{
    this->send(MessageFactory::produce(MessageFactory::TYPE_EDITOR_OPEN));
}

void GoMainWindow::on_toolButtonClose_clicked()
{
    this->send(MessageFactory::produce(MessageFactory::TYPE_EDITOR_CLOSE));
}

void GoMainWindow::on_toolButtonSave_clicked()
{
    this->send(MessageFactory::produce(MessageFactory::TYPE_EDITOR_SAVE));
}

void GoMainWindow::on_toolButtonSaveAs_clicked()
{
    this->send(MessageFactory::produce(MessageFactory::TYPE_EDITOR_SAVEAS));
}

void GoMainWindow::on_toolButtonSaveAll_clicked()
{
    this->send(MessageFactory::produce(MessageFactory::TYPE_EDITOR_SAVEALL));
}

void GoMainWindow::on_toolButtonAnalysis_clicked()
{
    this->send(MessageFactory::produce(MessageFactory::TYPE_EDITOR_ANALYSIS_PROBABILITY));
}

void GoMainWindow::on_toolButtonPath_clicked()
{
    this->send(MessageFactory::produce(MessageFactory::TYPE_EDITOR_ANALYSIS_PATH));
}

void GoMainWindow::on_toolButtonCut_clicked()
{
    this->send(MessageFactory::produce(MessageFactory::TYPE_EDITOR_ANALYSIS_CUT));
}

void GoMainWindow::on_toolButtonCopy_clicked()
{
    this->send(MessageFactory::produce(MessageFactory::TYPE_EDITOR_COPY));
}

void GoMainWindow::on_toolButtonDelete_clicked()
{
    this->send(MessageFactory::produce(MessageFactory::TYPE_EDITOR_DELETE));
}

void GoMainWindow::on_toolButtonZoomIn_clicked()
{
    this->send(MessageFactory::produce(MessageFactory::TYPE_EDITOR_ZOOM_IN));
}

void GoMainWindow::on_toolButtonZoomOut_clicked()
{
    this->send(MessageFactory::produce(MessageFactory::TYPE_EDITOR_ZOOM_OUT));
}

void GoMainWindow::on_toolButtonFeedback_clicked()
{
    this->send(MessageFactory::produce(MessageFactory::TYPE_EDITOR_SET_GLOBAL_FEEDBACK));
}

void GoMainWindow::on_toolButtonUnlockFb_clicked()
{
    this->send(MessageFactory::produce(MessageFactory::TYPE_EDITOR_UNSET_GLOBAL_FEEDBBACK));
}
