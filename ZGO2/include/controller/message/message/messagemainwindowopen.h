#ifndef MESSAGEMAINWINDOWOPEN_H
#define MESSAGEMAINWINDOWOPEN_H
/**
 * 主窗口加载完成消息。
 * 由主窗口发出，任何窗体都可以监听。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "message.h"

class MessageMainWindowOpen : public Message
{
public:
    MessageMainWindowOpen();
};

#endif // MESSAGEMAINWINDOWOPEN_H
