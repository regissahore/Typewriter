#include "toolboxgo.h"
#include "messagefactory.h"

/**
 * 构造函数。
 * @param parent 父窗体。
 */
ToolboxGO::ToolboxGO(QWidget *parent) :  ToolboxAbstract(parent)
{
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(scrollArea);
    this->setLayout(layout);
    QWidget *widget = new QWidget(scrollArea);
    this->_layout = new QVBoxLayout();
    this->_layout->setMargin(0);
    this->_layout->setSpacing(0);
    this->buttonGOPointer = new QPushButton(tr("Pointer"), this);
    this->connect(buttonGOPointer, SIGNAL(pressed()), this, SLOT(setToolGOPointer()));
    this->_layout->addWidget(buttonGOPointer);
    this->buttonSelect = new QPushButton(tr("Select"), this);
    this->connect(buttonSelect, SIGNAL(pressed()), this, SLOT(setToolSelect()));
    this->_layout->addWidget(buttonSelect);
    this->buttonGOText = new QPushButton(tr("Text"), this);
    this->connect(buttonGOText, SIGNAL(pressed()), this, SLOT(setToolGOText()));
    this->_layout->addWidget(buttonGOText);
    this->buttonGOOperator1 = new QPushButton(tr("Operator 1"), this);
    this->connect(buttonGOOperator1, SIGNAL(pressed()), this, SLOT(setToolGOOperator1()));
    this->_layout->addWidget(buttonGOOperator1);
    this->buttonGOOperator2 = new QPushButton(tr("Operator 2"), this);
    this->connect(buttonGOOperator2, SIGNAL(pressed()), this, SLOT(setToolGOOperator2()));
    this->_layout->addWidget(buttonGOOperator2);
    this->buttonGOOperator3 = new QPushButton(tr("Operator 3"), this);
    this->connect(buttonGOOperator3, SIGNAL(pressed()), this, SLOT(setToolGOOperator3()));
    this->_layout->addWidget(buttonGOOperator3);
    //this->buttonGOOperator4 = new QPushButton(tr("Operator 4"), this);
    //this->connect(buttonGOOperator4, SIGNAL(pressed()), this, SLOT(setToolGOOperator4()));
    //this->_layout->addWidget(buttonGOOperator4);
    this->buttonGOOperator5 = new QPushButton(tr("Operator 5"), this);
    this->connect(buttonGOOperator5, SIGNAL(pressed()), this, SLOT(setToolGOOperator5()));
    this->_layout->addWidget(buttonGOOperator5);
    this->buttonGOOperator6 = new QPushButton(tr("Operator 6"), this);
    this->connect(buttonGOOperator6, SIGNAL(pressed()), this, SLOT(setToolGOOperator6()));
    this->_layout->addWidget(buttonGOOperator6);
    this->buttonGOOperator7 = new QPushButton(tr("Operator 7"), this);
    this->connect(buttonGOOperator7, SIGNAL(pressed()), this, SLOT(setToolGOOperator7()));
    this->_layout->addWidget(buttonGOOperator7);
    //this->buttonGOOperator8 = new QPushButton(tr("Operator 8"), this);
    //this->connect(buttonGOOperator8, SIGNAL(pressed()), this, SLOT(setToolGOOperator8()));
    //this->_layout->addWidget(buttonGOOperator8);
    this->buttonGOOperator9 = new QPushButton(tr("Operator 9"), this);
    this->connect(buttonGOOperator9, SIGNAL(pressed()), this, SLOT(setToolGOOperator9()));
    this->_layout->addWidget(buttonGOOperator9);
    this->buttonGOOperator10 = new QPushButton(tr("Operator 10"), this);
    this->connect(buttonGOOperator10, SIGNAL(pressed()), this, SLOT(setToolGOOperator10()));
    this->_layout->addWidget(buttonGOOperator10);
    this->buttonGOOperator11 = new QPushButton(tr("Operator 11"), this);
    this->connect(buttonGOOperator11, SIGNAL(pressed()), this, SLOT(setToolGOOperator11()));
    this->_layout->addWidget(buttonGOOperator11);
    //this->buttonGOOperator12 = new QPushButton(tr("Operator 12"), this);
    //this->connect(buttonGOOperator12, SIGNAL(pressed()), this, SLOT(setToolGOOperator12()));
    //this->_layout->addWidget(buttonGOOperator12);
    //this->buttonGOOperator13 = new QPushButton(tr("Operator 13"), this);
    //this->connect(buttonGOOperator13, SIGNAL(pressed()), this, SLOT(setToolGOOperator13()));
    //this->_layout->addWidget(buttonGOOperator13);
    //this->buttonGOOperator14 = new QPushButton(tr("Operator 14"), this);
    //this->connect(buttonGOOperator14, SIGNAL(pressed()), this, SLOT(setToolGOOperator14()));
    //this->_layout->addWidget(buttonGOOperator14);
    //this->buttonGOOperator15 = new QPushButton(tr("Operator 15"), this);
    //this->connect(buttonGOOperator15, SIGNAL(pressed()), this, SLOT(setToolGOOperator15()));
    //this->_layout->addWidget(buttonGOOperator15);
    //this->buttonGOOperator16 = new QPushButton(tr("Operator 16"), this);
    //this->connect(buttonGOOperator16, SIGNAL(pressed()), this, SLOT(setToolGOOperator16()));
    //this->_layout->addWidget(buttonGOOperator16);
    //this->buttonGOOperator17 = new QPushButton(tr("Operator 17"), this);
    //this->connect(buttonGOOperator17, SIGNAL(pressed()), this, SLOT(setToolGOOperator17()));
    //this->_layout->addWidget(buttonGOOperator17);
    widget->setLayout(this->_layout);
    scrollArea->setWidget(widget);
    widget->resize(130, widget->size().height());
    scrollArea->show();
}

/**
 * 绑定消息。
 * @param controller 控制器。
 */
void ToolboxGO::bindMessage(MessageController *controller)
{
    this->Messager::bindMessage(controller);
}

void ToolboxGO::setToolGOPointer()
{
    Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOLTYPE_GO_POINTER_EXTEND;
    this->sendMessage(message);

}

void ToolboxGO::setToolSelect()
{
    Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_COMMON_SELECT;
    this->sendMessage(message);
}

void ToolboxGO::setToolGOText()
{
    Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_TEXT;
    this->sendMessage(message);
}

void ToolboxGO::setToolGOOperator1()
{
    Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_OPERATOR_1;
    this->sendMessage(message);
}

void ToolboxGO::setToolGOOperator2()
{
    Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_OPERATOR_2;
    this->sendMessage(message);
}

void ToolboxGO::setToolGOOperator3()
{
    Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_OPERATOR_3;
    this->sendMessage(message);
}

void ToolboxGO::setToolGOOperator4()
{
    Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_OPERATOR_4;
    this->sendMessage(message);
}

void ToolboxGO::setToolGOOperator5()
{
    Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_OPERATOR_5;
    this->sendMessage(message);
}

void ToolboxGO::setToolGOOperator6()
{
    Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_OPERATOR_6;
    this->sendMessage(message);
}

void ToolboxGO::setToolGOOperator7()
{
    Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_OPERATOR_7;
    this->sendMessage(message);
}

void ToolboxGO::setToolGOOperator8()
{
    Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_OPERATOR_8;
    this->sendMessage(message);
}

void ToolboxGO::setToolGOOperator9()
{
    Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_OPERATOR_9;
    this->sendMessage(message);
}

void ToolboxGO::setToolGOOperator10()
{
    Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_OPERATOR_10;
    this->sendMessage(message);
}

void ToolboxGO::setToolGOOperator11()
{
    Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_OPERATOR_11;
    this->sendMessage(message);
}

void ToolboxGO::setToolGOOperator12()
{
    Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_OPERATOR_12;
    this->sendMessage(message);
}

void ToolboxGO::setToolGOOperator13()
{
    Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_OPERATOR_13;
    this->sendMessage(message);
}

void ToolboxGO::setToolGOOperator14()
{
    Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_OPERATOR_14;
    this->sendMessage(message);
}

void ToolboxGO::setToolGOOperator15()
{
    Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_OPERATOR_15;
    this->sendMessage(message);
}

void ToolboxGO::setToolGOOperator16()
{
    Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_OPERATOR_16;
    this->sendMessage(message);
}

void ToolboxGO::setToolGOOperator17()
{
    Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_OPERATOR_17;
    this->sendMessage(message);
}
