#ifndef MESSAGEMAINWINDOWCLOSE_H
#define MESSAGEMAINWINDOWCLOSE_H
/**
 * 主窗口直接关闭的消息。
 * 由编辑器发出，主窗口监听。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "message.h"

class MessageMainWindowClose : public Message
{
public:
    MessageMainWindowClose();
};

#endif // MESSAGEMAINWINDOWCLOSE_H
