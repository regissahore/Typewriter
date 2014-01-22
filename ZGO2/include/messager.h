#ifndef MESSAGER_H
#define MESSAGER_H

#include "messagecontroller.h"
#include "messagecreator.h"
#include "messagelistener.h"

class Messager : public MessageCreator, public MessageListener
{
public:
    Messager();
    virtual ~Messager();
    virtual void bindMessage(MessageController *controller);
};

#endif // MESSAGER_H
