#include <QPushButton>
#include "ToolboxGoMarkov.h"
#include "ui_ToolboxGoMarkov.h"
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

void ToolboxGoMarkov::bindMessage()
{
    this->listen(MessageFactory::TYPE_TOOL_SELECTION);
}

void ToolboxGoMarkov::messageEvent(QSharedPointer<Message> message)
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
        case DefinationToolType::TOOL_TYPE_GO_MARKOV_COMMON_CAUSE:
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
    QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_POINTER_EXTEND;
    this->send(message);
}

void ToolboxGoMarkov::on_buttonSelect_clicked()
{
    QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_COMMON_SELECT;
    this->send(message);
}

void ToolboxGoMarkov::on_buttonText_clicked()
{
    QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_TEXT;
    this->send(message);
}

void ToolboxGoMarkov::on_buttonEquivalent_clicked()
{
    QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_EQUIVALENT;
    this->send(message);
}

void ToolboxGoMarkov::on_buttonCommonCause_clicked()
{
    QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_COMMON_CAUSE;
    this->send(message);
}


void ToolboxGoMarkov::on_buttonOperator1_clicked()
{
    QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_1;
    this->send(message);
}

void ToolboxGoMarkov::on_buttonOperator2_clicked()
{
    QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_2;
    this->send(message);
}

void ToolboxGoMarkov::on_buttonOperator5_clicked()
{
    QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_5;
    this->send(message);
}

void ToolboxGoMarkov::on_buttonOperator6_clicked()
{
    QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_6;
    this->send(message);
}

void ToolboxGoMarkov::on_buttonOperator9A1_clicked()
{
    QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_9A1;
    this->send(message);
}

void ToolboxGoMarkov::on_buttonOperator9A2_clicked()
{
    QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_9A2;
    this->send(message);
}

void ToolboxGoMarkov::on_buttonOperator9B1_clicked()
{
    QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_9B1;
    this->send(message);
}

void ToolboxGoMarkov::on_buttonOperator9B2_clicked()
{
    QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_9B2;
    this->send(message);
}

void ToolboxGoMarkov::on_buttonOperator10_clicked()
{
    QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_10;
    this->send(message);
}

void ToolboxGoMarkov::on_buttonOperator11A_clicked()
{
    QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_11A;
    this->send(message);
}

void ToolboxGoMarkov::on_buttonOperator12A_clicked()
{
    QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_12A;
    this->send(message);
}

void ToolboxGoMarkov::on_buttonOperator13A_clicked()
{
    QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_13A;
    this->send(message);
}

void ToolboxGoMarkov::on_buttonOperator13B_clicked()
{
    QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_13B;
    this->send(message);
}

void ToolboxGoMarkov::on_buttonOperator15A_clicked()
{
    QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_15A;
    this->send(message);
}

void ToolboxGoMarkov::on_buttonOperator15B_clicked()
{
    QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_15B;
    this->send(message);
}

void ToolboxGoMarkov::on_buttonOperator16_clicked()
{
    QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_16;
    this->send(message);
}

void ToolboxGoMarkov::on_buttonOperator17_clicked()
{
    QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_17;
    this->send(message);
}

void ToolboxGoMarkov::on_buttonOperator18_clicked()
{
    QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_18;
    this->send(message);
}

void ToolboxGoMarkov::on_buttonOperator18A_clicked()
{
    QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_18A;
    this->send(message);
}

void ToolboxGoMarkov::on_buttonOperator19_clicked()
{
    QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_19;
    this->send(message);
}

void ToolboxGoMarkov::on_buttonOperator20_clicked()
{
    QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_20;
    this->send(message);
}

void ToolboxGoMarkov::on_buttonOperator21_clicked()
{
    QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_21;
    this->send(message);
}

void ToolboxGoMarkov::on_buttonOperator22A_clicked()
{
    QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_22A;
    this->send(message);
}

void ToolboxGoMarkov::on_buttonOperator22B_clicked()
{
    QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_22B;
    this->send(message);
}

void ToolboxGoMarkov::on_buttonOperator23_clicked()
{
    QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_23;
    this->send(message);
}

void ToolboxGoMarkov::on_buttonOperatorSplit_clicked()
{
    QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_SPLIT;
    this->send(message);
}
