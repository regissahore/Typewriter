#ifndef MESSAGER_H
#define MESSAGER_H

#include "MessageController.h"
#include "MessageCreator.h"
#include "MessageListener.h"

class Messager : public MessageCreator, public MessageListener
{
public:
    Messager();
    virtual ~Messager();
    virtual void bindMessage(MessageController *controller);
};

#endif // MESSAGER_H
