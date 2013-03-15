#include "controller/messagefactory.h"

int MessageFactory::_id = 0;

/**
 * 构造函数。
 */
MessageFactory::MessageFactory()
{
}

/**
 * 产生消息并赋予消息ID，不要重载此函数。
 * @param type 消息的类型。
 */
Message* MessageFactory::produce(int type)
{
    Message *message = this->produceMessage(type);
    if (message != 0L)
    {
        message->setId(MessageFactory::_id++);
    }
    return message;
}

/**
 * 获取消息的名称。
 * @param type 消息的类型。
 */
QString MessageFactory::getMessageName(int type)
{
    Message *message = produceMessage(type);
    if (message != 0L)
    {
        return message->name();
    }
    return "";
}

/**
 * 获取所有可以生成的事件名称的列表，用于程序的调试。
 * 为了本函数的正常运行，消息类别编号应该从0开始依次赋值，或用enum实现。
 * @return 事件名称的列表。
 */
QVector<QString> MessageFactory::getMessageNameVector()
{
    QVector<QString> names;
    for (int i = 0; ; ++i)
    {
        QString name = this->getMessageName(i);
        if ("" == name)
        {
            break;
        }
        names.push_back(name);
    }
    return names;
}

/**
 * 产生消息。
 * @param type 消息的类型。
 */
Message* MessageFactory::produceMessage(int type)
{
    Q_UNUSED(type);
    return 0L;
}

