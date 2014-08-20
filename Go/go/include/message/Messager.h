#ifndef MESSAGER_H
#define MESSAGER_H

#include "MessageController.h"

class Messager
{
public:
    Messager();
    virtual ~Messager();
    void send(QSharedPointer<Message> message);
    void listen(int messageType);
    virtual void messageEvent(QSharedPointer<Message> message);
};

#endif // MESSAGER_H
