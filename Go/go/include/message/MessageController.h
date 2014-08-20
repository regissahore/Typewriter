#ifndef MESSAGECONTROLLER_H
#define MESSAGECONTROLLER_H
#include "stable.h"
#include "Message.h"

class Messager;

class MessageController
{
public:
    static MessageController* instance();
    virtual ~MessageController();
    void send(QSharedPointer<Message> message);
    void listen(int messageType, Messager *listener);
    void release(Messager *listener);

protected:
    QMap<int, QVector<Messager*> > _listeners;
    MessageController();
    static MessageController* _instance;
};

#endif // MESSAGECONTROLLER_H
