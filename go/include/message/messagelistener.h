#ifndef MESSAGELISTENER_H
#define MESSAGELISTENER_H
#include <QVector>
#include <QString>
#include "Message.h"
#include "MessageController.h"

class MessageController;

class MessageListener
{
public:
    MessageListener();
    virtual ~MessageListener();
    void releaseListener();
    void setMessageController(MessageController *messageController);
    void addListenedMessage(int messageType);
    virtual void messageEvent(QSharedPointer<Message> message);

protected:
    QVector<int> *_messageListened;
    MessageController *_messageController;
};

#endif // MESSAGELISTENER_H
