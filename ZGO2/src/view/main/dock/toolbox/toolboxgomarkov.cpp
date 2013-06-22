#include <QPushButton>
#include "toolboxgomarkov.h"
#include "ui_toolboxgomarkov.h"
#include "messagefactory.h"
#include "definationtooltype.h"

ToolboxGOMarkov::ToolboxGOMarkov(QWidget *parent) :
    ToolboxAbstract(parent),
    ui(new Ui::ToolboxGOMarkov)
{
    ui->setupUi(this);
}

ToolboxGOMarkov::~ToolboxGOMarkov()
{
    this->ToolboxAbstract::~ToolboxAbstract();
    delete ui;
}

void ToolboxGOMarkov::bindMessage(MessageController *controller)
{
    this->Messager::bindMessage(controller);
    controller->listen(MessageFactory::TYPE_TOOL_SELECTION, this);
}

void ToolboxGOMarkov::messageEvent(Message *message)
{
    if (message->type() == MessageFactory::TYPE_TOOL_SELECTION)
    {
        switch(message->paramInt)
        {
        case DefinationToolType::TOOL_TYPE_GO_POINTER_EXTEND:
            this->setSelectedTool(this->ui->buttonPointer);
            break;
        case DefinationToolType::TOOL_TYPE_COMMON_SELECT:
            this->setSelectedTool(this->ui->buttonSelect);
            break;
        case DefinationToolType::TOOL_TYPE_GO_TEXT:
            this->setSelectedTool(this->ui->buttonText);
            break;
        case DefinationToolType::TOOL_TYPE_GO_OPERATOR_1:
            this->setSelectedTool(this->ui->buttonOperator1);
            break;
        case DefinationToolType::TOOL_TYPE_GO_OPERATOR_2:
            this->setSelectedTool(this->ui->buttonOperator2);
            break;
        case DefinationToolType::TOOL_TYPE_GO_OPERATOR_3:
            this->setSelectedTool(this->ui->buttonOperator3);
            break;
        case DefinationToolType::TOOL_TYPE_GO_OPERATOR_4:
            //this->setSelectedTool(this->ui->buttonOperator4);
            break;
        case DefinationToolType::TOOL_TYPE_GO_OPERATOR_5:
            this->setSelectedTool(this->ui->buttonOperator5);
            break;
        case DefinationToolType::TOOL_TYPE_GO_OPERATOR_6:
            this->setSelectedTool(this->ui->buttonOperator6);
            break;
        case DefinationToolType::TOOL_TYPE_GO_OPERATOR_7:
            this->setSelectedTool(this->ui->buttonOperator7);
            break;
        case DefinationToolType::TOOL_TYPE_GO_OPERATOR_8:
            //this->setSelectedTool(this->ui->buttonOperator8);
            break;
        case DefinationToolType::TOOL_TYPE_GO_OPERATOR_9:
            this->setSelectedTool(this->ui->buttonOperator9);
            break;
        case DefinationToolType::TOOL_TYPE_GO_OPERATOR_10:
            this->setSelectedTool(this->ui->buttonOperator10);
            break;
        case DefinationToolType::TOOL_TYPE_GO_OPERATOR_11:
            this->setSelectedTool(this->ui->buttonOperator11);
            break;
        case DefinationToolType::TOOL_TYPE_GO_OPERATOR_12:
            //this->setSelectedTool(this->ui->buttonOperator12);
            break;
        case DefinationToolType::TOOL_TYPE_GO_OPERATOR_13:
           // this->setSelectedTool(this->ui->buttonOperator13);
            break;
        case DefinationToolType::TOOL_TYPE_GO_OPERATOR_14:
            //this->setSelectedTool(this->ui->buttonOperator14);
            break;
        case DefinationToolType::TOOL_TYPE_GO_OPERATOR_15:
            //this->setSelectedTool(this->ui->buttonOperator15);
            break;
        case DefinationToolType::TOOL_TYPE_GO_OPERATOR_16:
            //this->setSelectedTool(this->ui->buttonOperator16);
            break;
        case DefinationToolType::TOOL_TYPE_GO_OPERATOR_17:
            //this->setSelectedTool(this->ui->buttonOperator17);
            break;
        }
    }
}

void ToolboxGOMarkov::on_buttonPointer_clicked()
{
    Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_POINTER_EXTEND;
    this->sendMessage(message);
}

void ToolboxGOMarkov::on_buttonSelect_clicked()
{
    Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_COMMON_SELECT;
    this->sendMessage(message);
}

void ToolboxGOMarkov::on_buttonText_clicked()
{
    Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_TEXT;
    this->sendMessage(message);
}

void ToolboxGOMarkov::on_buttonEquivalent_clicked()
{
    Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_EQUIVALENT;
    this->sendMessage(message);
}

void ToolboxGOMarkov::on_pushButton_clicked()
{
    Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_COMMON_CAUSE;
    this->sendMessage(message);
}

void ToolboxGOMarkov::on_buttonOperator1_clicked()
{
    Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_1;
    this->sendMessage(message);
}

void ToolboxGOMarkov::on_buttonOperator2_clicked()
{
    Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_2;
    this->sendMessage(message);
}

void ToolboxGOMarkov::on_buttonOperator3_clicked()
{
    Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_3;
    this->sendMessage(message);
}

void ToolboxGOMarkov::on_buttonOperator5_clicked()
{
    Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_5;
    this->sendMessage(message);
}

void ToolboxGOMarkov::on_buttonOperator6_clicked()
{
    Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_6;
    this->sendMessage(message);
}

void ToolboxGOMarkov::on_buttonOperator7_clicked()
{
    Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_7;
    this->sendMessage(message);
}

void ToolboxGOMarkov::on_buttonOperator9_clicked()
{
    Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_9;
    this->sendMessage(message);
}

void ToolboxGOMarkov::on_buttonOperator10_clicked()
{
    Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_10;
    this->sendMessage(message);
}

void ToolboxGOMarkov::on_buttonOperator11_clicked()
{
    Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_11;
    this->sendMessage(message);
}
