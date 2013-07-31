#ifndef MESSAGER_H
#define MESSAGER_H
/**
 * 同时具有发送和监听功能的基类，如果需要全局消息功能建议继承此类。
 * @author ZHG <CyberZHG@gmail.com>
 */

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
