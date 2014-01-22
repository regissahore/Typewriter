#include <QLabel>
#include "outputconsole.h"
#include "ui_outputconsole.h"
#include "messagefactory.h"

OutputConsole::OutputConsole(QWidget *parent) :
    QWidget(parent), Messager(),
    ui(new Ui::OutputConsole)
{
    ui->setupUi(this);
}

OutputConsole::~OutputConsole()
{
    delete ui;
    this->Messager::~Messager();
}

void OutputConsole::bindMessage(MessageController *controller)
{
    controller->listen(MessageFactory::TYPE_OUTPUT_CLEAR, this);
    controller->listen(MessageFactory::TYPE_OUTPUT_TEXT, this);
    controller->listen(MessageFactory::TYPE_OUTPUT_SAMELINE_TEXT, this);
    controller->listen(MessageFactory::TYPE_OUTPUT_CORRECT, this);
    controller->listen(MessageFactory::TYPE_OUTPUT_ERROR, this);
}

void OutputConsole::messageEvent(QSharedPointer<Message> message)
{
    QLabel *label = 0L;
    switch (message->type())
    {
    case MessageFactory::TYPE_OUTPUT_CLEAR:
        this->ui->listWidget->clear();
        break;
    case MessageFactory::TYPE_OUTPUT_TEXT:
        this->ui->listWidget->addItem("");
        label = new QLabel(this);
        label->setText(message->paramString);;
        this->ui->listWidget->setItemWidget(this->ui->listWidget->item(this->ui->listWidget->count() - 1), label);
        break;
    case MessageFactory::TYPE_OUTPUT_SAMELINE_TEXT:
        if (this->ui->listWidget->count())
        {
            this->ui->listWidget->item(this->ui->listWidget->count() - 1)->setText("");
        }
        else
        {
            this->ui->listWidget->addItem("");
        }
        label = new QLabel(this);
        label->setText(message->paramString);;
        this->ui->listWidget->setItemWidget(this->ui->listWidget->item(this->ui->listWidget->count() - 1), label);
    case MessageFactory::TYPE_OUTPUT_CORRECT:
        this->ui->listWidget->addItem("");
        label = new QLabel(this);
        label->setText(message->paramString);
        label->setStyleSheet("color: rgb(26, 130, 14);");
        this->ui->listWidget->setItemWidget(this->ui->listWidget->item(this->ui->listWidget->count() - 1), label);
        break;
    case MessageFactory::TYPE_OUTPUT_ERROR:
        this->ui->listWidget->addItem("");
        label = new QLabel(this);
        label->setText(message->paramString);
        label->setStyleSheet("color: rgb(172, 25, 25)");
        this->ui->listWidget->setItemWidget(this->ui->listWidget->item(this->ui->listWidget->count() - 1), label);
        break;
    }
}
