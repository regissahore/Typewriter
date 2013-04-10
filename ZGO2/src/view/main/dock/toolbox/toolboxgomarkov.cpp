#include "toolboxgomarkov.h"
#include "messagefactory.h"

ToolboxGOMarkov::ToolboxGOMarkov(QWidget *parent) : ToolboxGO(parent)
{
    this->buttonGOEquivalent = new QPushButton(tr("Equivalent"), this);
    this->connect(buttonGOEquivalent, SIGNAL(pressed()), this, SLOT(setToolGOEquivalent()));
    this->_layout->addWidget(buttonGOEquivalent);
}

void ToolboxGOMarkov::setToolGOEquivalent()
{
    Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_EQUIVALENT;
    this->sendMessage(message);
}

void ToolboxGOMarkov::setToolGOOperator1()
{
    Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_1;
    this->sendMessage(message);
}

void ToolboxGOMarkov::setToolGOOperator2()
{
    Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_2;
    this->sendMessage(message);
}

void ToolboxGOMarkov::setToolGOOperator3()
{
    Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_3;
    this->sendMessage(message);
}

void ToolboxGOMarkov::setToolGOOperator4()
{
    Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_4;
    this->sendMessage(message);
}

void ToolboxGOMarkov::setToolGOOperator5()
{
    Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_5;
    this->sendMessage(message);
}

void ToolboxGOMarkov::setToolGOOperator6()
{
    Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_6;
    this->sendMessage(message);
}

void ToolboxGOMarkov::setToolGOOperator7()
{
    Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_7;
    this->sendMessage(message);
}

void ToolboxGOMarkov::setToolGOOperator8()
{
    Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_8;
    this->sendMessage(message);
}

void ToolboxGOMarkov::setToolGOOperator9()
{
    Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_9;
    this->sendMessage(message);
}

void ToolboxGOMarkov::setToolGOOperator10()
{
    Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_10;
    this->sendMessage(message);
}

void ToolboxGOMarkov::setToolGOOperator11()
{
    Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_11;
    this->sendMessage(message);
}

void ToolboxGOMarkov::setToolGOOperator12()
{
    Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_12;
    this->sendMessage(message);
}

void ToolboxGOMarkov::setToolGOOperator13()
{
    Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_13;
    this->sendMessage(message);
}

void ToolboxGOMarkov::setToolGOOperator14()
{
    Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_14;
    this->sendMessage(message);
}

void ToolboxGOMarkov::setToolGOOperator15()
{
    Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_15;
    this->sendMessage(message);
}

void ToolboxGOMarkov::setToolGOOperator16()
{
    Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_16;
    this->sendMessage(message);
}

void ToolboxGOMarkov::setToolGOOperator17()
{
    Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_17;
    this->sendMessage(message);
}
