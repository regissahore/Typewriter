#include "controller/message.h"

/**
 * 构造函数。
 */
Message::Message()
{
}

/**
 * 返回消息内容，消息的结构由特定的消息类型决定，也可以为空。
 * @return 消息内容。
 */
QString Message::message() const
{
    return this->_message;
}

/**
 * 设置消息内容。
 * @param message 消息内容。
 */
void Message::setMessage(QString message)
{
    this->_message = message;
}
