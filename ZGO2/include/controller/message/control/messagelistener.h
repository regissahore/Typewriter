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
    ~MessageListener();
    void setMessageController(MessageController *messageController);
    void addListenedMessage(QString message);
    virtual void messageEvent(Message *message);

protected:
    QVector<QString> *_messageListened;
    MessageController *_messageController;
};

#endif // MESSAGELISTENER_H
