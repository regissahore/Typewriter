#include "messager.h"

/**
 * 构造函数。
 */
Messager::Messager() : MessageCreator(), MessageListener()
{
}

Messager::~Messager()
{
    this->MessageListener::~MessageListener();
}

/**
 * 绑定监听。
 * @param controller 消息管理器。
 */
void Messager::bindMessage(MessageController *controller)
{
    this->MessageCreator::setMessageController(controller);
    this->MessageListener::setMessageController(controller);
}
