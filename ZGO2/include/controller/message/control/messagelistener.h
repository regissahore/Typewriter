#ifndef MESSAGELISTENER_H
#define MESSAGELISTENER_H
/**
 * 用于监听消息，如果想继承此类请直接引用MessageController.h文件。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QVector>
#include <QString>
#include "message.h"
#include "messagecontroller.h"

class MessageController;

class MessageListener
{
public:
    MessageListener();
    virtual ~MessageListener();
    void releaseListener();
    void setMessageController(MessageController *messageController);
    void addListenedMessage(int messageType);
    virtual void messageEvent(Message *message);

protected:
    QVector<int> *_messageListened;
    MessageController *_messageController;
};

#endif // MESSAGELISTENER_H
