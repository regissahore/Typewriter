#include "view/debugconsole.h"

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
    QVector<QString> messageNames;
    MessageFactory* factory;
    // 添加对主窗口时间的监听。
    factory = new MessageFactoryMainWindow();
    messageNames = factory->getMessageNameVector();
    for (int i = 0; i < messageNames.size(); ++i)
    {
        controller->listen(messageNames[i], this);
    }
    delete factory;
    messageNames.clear();
}

/**
 * 输出消息内容。
 * @reutrn param message 消息。
 */
void DebugConsole::messageEvent(Message *message)
{
    if (message->message() == "")
    {
        this->_textEdit->append(QString("[%1] ").arg(message->id()) + message->name());
    }
    else
    {
        this->_textEdit->append(QString("[%1] ").arg(message->id()) + message->name() + ": " + message->message());
    }
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
