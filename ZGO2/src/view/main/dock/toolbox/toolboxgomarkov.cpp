#include "toolboxgomarkov.h"
#include "messagefactory.h"

ToolboxGOMarkov::ToolboxGOMarkov(QWidget *parent) : ToolboxGO(parent)
{
    this->_buttonGOEquivalent = new QPushButton(tr("Equivalent"), this);
    this->connect(this->_buttonGOEquivalent, SIGNAL(pressed()), this, SLOT(setToolGOEquivalent()));
    this->_layout->addWidget(this->_buttonGOEquivalent);

    this->_buttonGOCommonCause = new QPushButton(tr("Common Cause"), this);
    this->connect(this->_buttonGOCommonCause, SIGNAL(pressed()), this, SLOT(setToolGOCommonCause()));
    this->_layout->addWidget(this->_buttonGOCommonCause);
}

void ToolboxGOMarkov::messageEvent(Message *message)
{
    if (message->type() == MessageFactory::TYPE_TOOL_SELECTION)
    {
        switch(message->paramInt)
        {
        case DefinationToolType::TOOL_TYPE_GO_MARKOV_POINTER_EXTEND:
            this->setSelectedTool(this->_buttonGOPointer);
            break;
        case DefinationToolType::TOOL_TYPE_COMMON_SELECT:
            this->setSelectedTool(this->_buttonSelect);
            break;
        case DefinationToolType::TOOL_TYPE_GO_MARKOV_TEXT:
            this->setSelectedTool(this->_buttonGOText);
            break;
        case DefinationToolType::TOOL_TYPE_GO_MARKOV_EQUIVALENT:
            this->setSelectedTool(this->_buttonGOEquivalent);
            break;
        case DefinationToolType::TOOL_TYPE_GO_MARKOV_COMMON_CAUSE:
            this->setSelectedTool(this->_buttonGOCommonCause);
            break;
        case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_1:
            this->setSelectedTool(this->_buttonGOOperator1);
            break;
        case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_2:
            this->setSelectedTool(this->_buttonGOOperator2);
            break;
        case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_3:
            this->setSelectedTool(this->_buttonGOOperator3);
            break;
        case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_4:
            this->setSelectedTool(this->_buttonGOOperator4);
            break;
        case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_5:
            this->setSelectedTool(this->_buttonGOOperator5);
            break;
        case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_6:
            this->setSelectedTool(this->_buttonGOOperator6);
            break;
        case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_7:
            this->setSelectedTool(this->_buttonGOOperator7);
            break;
        case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_8:
            this->setSelectedTool(this->_buttonGOOperator8);
            break;
        case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_9:
            this->setSelectedTool(this->_buttonGOOperator9);
            break;
        case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_10:
            this->setSelectedTool(this->_buttonGOOperator10);
            break;
        case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_11:
            this->setSelectedTool(this->_buttonGOOperator11);
            break;
        case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_12:
            this->setSelectedTool(this->_buttonGOOperator12);
            break;
        case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_13:
            this->setSelectedTool(this->_buttonGOOperator13);
            break;
        case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_14:
            this->setSelectedTool(this->_buttonGOOperator14);
            break;
        case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_15:
            this->setSelectedTool(this->_buttonGOOperator15);
            break;
        case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_16:
            this->setSelectedTool(this->_buttonGOOperator16);
            break;
        case DefinationToolType::TOOL_TYPE_GO_MARKOV_OPERATOR_17:
            this->setSelectedTool(this->_buttonGOOperator17);
            break;
        }
    }
}

void ToolboxGOMarkov::setToolGOPointer()
{
    Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_POINTER_EXTEND;
    this->sendMessage(message);
}

void ToolboxGOMarkov::setToolGOEquivalent()
{
    Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_EQUIVALENT;
    this->sendMessage(message);
}

void ToolboxGOMarkov::setToolGOCommonCause()
{
    Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_COMMON_CAUSE;
    this->sendMessage(message);
}

void ToolboxGOMarkov::setToolGOText()
{
    Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_TEXT;
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
