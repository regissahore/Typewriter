#include "debugconsole.h"
#include "messagefactory.h"

/**
 * 构造函数。
 */
DebugConsole::DebugConsole(QWidget *parent) : QWidget(parent), Messager()
{
    this->_textEdit = new QTextEdit(this);
    this->_textEdit->setReadOnly(true);
    QGridLayout *layout = new QGridLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(this->_textEdit);
    this->setLayout(layout);
    this->connect(this->_textEdit, SIGNAL(textChanged()), this, SLOT(decreaseText()));
}

/**
 * 绑定事件。
 * @param controller 事件控制器。
 */
void DebugConsole::bindMessage(MessageController *controller)
{
    QList<int> messageTypes = MessageFactory::getMessageTypeList();
    for (int i = 0; i < messageTypes.size(); ++i)
    {
        controller->listen(messageTypes[i], this);
    }
    messageTypes.clear();
}

/**
 * 输出消息内容。
 * @return param message 消息。
 */
void DebugConsole::messageEvent(QSharedPointer<Message> message)
{
    this->_textEdit->append(QObject::tr("[%1] ").arg(message->id()) + MessageFactory::getMessageTypeName(message->type()) + QObject::tr(" : %1 ").arg(message->paramInt) + message->paramString);
}

/**
 * 文字发生改变时触发。
 */
void DebugConsole::decreaseText()
{
    if (this->_textEdit->toPlainText().length() > 65535)
    {
        this->_textEdit->setPlainText(this->_textEdit->toPlainText().right(65535));
    }
}
