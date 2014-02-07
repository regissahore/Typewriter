#include <QPushButton>
#include "ToolboxGoMarkov.h"
#include "ui_toolboxgomarkov.h"
#include "MessageFactory.h"
#include "DefinationToolType.h"
using namespace std;

ToolboxGoMarkov::ToolboxGoMarkov(QWidget *parent) :
    ToolboxAbstract(parent),
    ui(new Ui::ToolboxGoMarkov)
{
    ui->setupUi(this);
}

ToolboxGoMarkov::~ToolboxGoMarkov()
{
    delete ui;
}

void ToolboxGoMarkov::bindMessage(MessageController *controller)
{
    this->Messager::bindMessage(controller);
    controller->listen(MessageFactory::TYPE_TOOL_SELECTION, this);
}

void ToolboxGoMarkov::messageEvent(shared_ptr<Message> message)
{
    if (message->type() == MessageFactory::TYPE_TOOL_SELECTION)
    {
        switch(message->paramInt)
        {
        case DefinationToolType::TOOL_TYPE_GO_MARKOV_POINTER_EXTEND:
            this->setSelectedTool(this->ui->buttonPointer);
            break;
        case DefinationToolType::TOOL_TYPE_COMMON_SELECT:
            this->setSelectedTool(this->ui->buttonSelect);
            break;
        case DefinationToolType::TOOL_TYPE_GO_TEXT:
            this->setSelectedTool(this->ui->buttonText);
            break;
        case DefinationToolType::TOOL_TYPE_GO_MARKOV_EQUIVALENT:
            this->setSelectedTool(this->ui->buttonEquivalent);
            break;
        case DefinationToolType::TOOL_TYPE_GO_MARKOV_COMMON_CAUSE_2:
            this->setSelectedTool(this->ui->buttonCommonCause);
            break;
        case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_1:
            this->setSelectedTool(this->ui->buttonOperator1);
            break;
        case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_2:
            this->setSelectedTool(this->ui->buttonOperator2);
            break;
        case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_5:
            this->setSelectedTool(this->ui->buttonOperator5);
            break;
        case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_6:
            this->setSelectedTool(this->ui->buttonOperator6);
            break;
        case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_9A1:
            this->setSelectedTool(this->ui->buttonOperator9A1);
            break;
        case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_9A2:
            this->setSelectedTool(this->ui->buttonOperator9A2);
            break;
        case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_9B1:
            this->setSelectedTool(this->ui->buttonOperator9B1);
            break;
        case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_9B2:
            this->setSelectedTool(this->ui->buttonOperator9B2);
            break;
        case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_10:
            this->setSelectedTool(this->ui->buttonOperator10);
            break;
        case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_11A:
            this->setSelectedTool(this->ui->buttonOperator11A);
            break;
        case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_12A:
            this->setSelectedTool(this->ui->buttonOperator12A);
            break;
        case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_13A:
            this->setSelectedTool(this->ui->buttonOperator13A);
            break;
        case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_13B:
            this->setSelectedTool(this->ui->buttonOperator13B);
            break;
        case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_15A:
            this->setSelectedTool(this->ui->buttonOperator15A);
            break;
        case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_15B:
            this->setSelectedTool(this->ui->buttonOperator15B);
            break;
        case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_16:
            this->setSelectedTool(this->ui->buttonOperator16);
            break;
        case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_17:
            this->setSelectedTool(this->ui->buttonOperator17);
            break;
        case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_18:
            this->setSelectedTool(this->ui->buttonOperator18);
            break;
        case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_18A:
            this->setSelectedTool(this->ui->buttonOperator18A);
            break;
        case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_19:
            this->setSelectedTool(this->ui->buttonOperator19);
            break;
        case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_20:
            this->setSelectedTool(this->ui->buttonOperator20);
            break;
        case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_21:
            this->setSelectedTool(this->ui->buttonOperator21);
            break;
        case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_22A:
            this->setSelectedTool(this->ui->buttonOperator22A);
            break;
        case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_22B:
            this->setSelectedTool(this->ui->buttonOperator22B);
            break;
        case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_SPLIT:
            this->setSelectedTool(this->ui->buttonOperatorSplit);
            break;
        }
    }
}

void ToolboxGoMarkov::on_buttonPointer_clicked()
{
    shared_ptr<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_POINTER_EXTEND;
    this->sendMessage(message);
}

void ToolboxGoMarkov::on_buttonSelect_clicked()
{
    shared_ptr<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_COMMON_SELECT;
    this->sendMessage(message);
}

void ToolboxGoMarkov::on_buttonText_clicked()
{
    shared_ptr<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_TEXT;
    this->sendMessage(message);
}

void ToolboxGoMarkov::on_buttonEquivalent_clicked()
{
    shared_ptr<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_EQUIVALENT;
    this->sendMessage(message);
}

void ToolboxGoMarkov::on_buttonCommonCause_clicked()
{
    shared_ptr<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_COMMON_CAUSE_2;
    this->sendMessage(message);
}


void ToolboxGoMarkov::on_buttonOperator1_clicked()
{
    shared_ptr<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_1;
    this->sendMessage(message);
}

void ToolboxGoMarkov::on_buttonOperator2_clicked()
{
    shared_ptr<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_2;
    this->sendMessage(message);
}

void ToolboxGoMarkov::on_buttonOperator5_clicked()
{
    shared_ptr<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_5;
    this->sendMessage(message);
}

void ToolboxGoMarkov::on_buttonOperator6_clicked()
{
    shared_ptr<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_6;
    this->sendMessage(message);
}

void ToolboxGoMarkov::on_buttonOperator9A1_clicked()
{
    shared_ptr<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_9A1;
    this->sendMessage(message);
}

void ToolboxGoMarkov::on_buttonOperator9A2_clicked()
{
    shared_ptr<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_9A2;
    this->sendMessage(message);
}

void ToolboxGoMarkov::on_buttonOperator9B1_clicked()
{
    shared_ptr<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_9B1;
    this->sendMessage(message);
}

void ToolboxGoMarkov::on_buttonOperator9B2_clicked()
{
    shared_ptr<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_9B2;
    this->sendMessage(message);
}

void ToolboxGoMarkov::on_buttonOperator10_clicked()
{
    shared_ptr<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_10;
    this->sendMessage(message);
}

void ToolboxGoMarkov::on_buttonOperator11A_clicked()
{
    shared_ptr<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_11A;
    this->sendMessage(message);
}

void ToolboxGoMarkov::on_buttonOperator12A_clicked()
{
    shared_ptr<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_12A;
    this->sendMessage(message);
}

void ToolboxGoMarkov::on_buttonOperator13A_clicked()
{
    shared_ptr<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_13A;
    this->sendMessage(message);
}

void ToolboxGoMarkov::on_buttonOperator13B_clicked()
{
    shared_ptr<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_13B;
    this->sendMessage(message);
}

void ToolboxGoMarkov::on_buttonOperator15A_clicked()
{
    shared_ptr<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_15A;
    this->sendMessage(message);
}

void ToolboxGoMarkov::on_buttonOperator15B_clicked()
{
    shared_ptr<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_15B;
    this->sendMessage(message);
}

void ToolboxGoMarkov::on_buttonOperator16_clicked()
{
    shared_ptr<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_16;
    this->sendMessage(message);
}

void ToolboxGoMarkov::on_buttonOperator17_clicked()
{
    shared_ptr<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_17;
    this->sendMessage(message);
}

void ToolboxGoMarkov::on_buttonOperator18_clicked()
{
    shared_ptr<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_18;
    this->sendMessage(message);
}

void ToolboxGoMarkov::on_buttonOperator18A_clicked()
{
    shared_ptr<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_18A;
    this->sendMessage(message);
}

void ToolboxGoMarkov::on_buttonOperator19_clicked()
{
    shared_ptr<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_19;
    this->sendMessage(message);
}

void ToolboxGoMarkov::on_buttonOperator20_clicked()
{
    shared_ptr<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_20;
    this->sendMessage(message);
}

void ToolboxGoMarkov::on_buttonOperator21_clicked()
{
    shared_ptr<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_21;
    this->sendMessage(message);
}

void ToolboxGoMarkov::on_buttonOperator22A_clicked()
{
    shared_ptr<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_22A;
    this->sendMessage(message);
}

void ToolboxGoMarkov::on_buttonOperator22B_clicked()
{
    shared_ptr<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_22B;
    this->sendMessage(message);
}

void ToolboxGoMarkov::on_buttonOperator23_clicked()
{
    shared_ptr<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_23;
    this->sendMessage(message);
}

void ToolboxGoMarkov::on_buttonOperatorSplit_clicked()
{
    shared_ptr<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_SPLIT;
    this->sendMessage(message);
}
