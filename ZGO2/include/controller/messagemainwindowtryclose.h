#ifndef MESSAGEMAINWINDOWTRYCLOSE_H
#define MESSAGEMAINWINDOWTRYCLOSE_H
/**
 * 主窗口尝试关闭的消息。
 * 由和关闭主窗口相关的操作产生，编辑器监听。
 * @author ZHG <CyberZHG@gmail.com>
 */

#include "controller/message.h"

class MessageMainWindowTryClose : public Message
{
public:
    MessageMainWindowTryClose();
};

#endif // MESSAGEMAINWINDOWTRYCLOSE_H
