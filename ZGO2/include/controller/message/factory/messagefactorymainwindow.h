#ifndef MESSAGEFACTORYMAINWINDOW_H
#define MESSAGEFACTORYMAINWINDOW_H
/**
 * 生成主窗口的消息。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "messagefactory.h"
#include "messagemainwindowopen.h"
#include "messagemainwindowtryclose.h"
#include "messagemainwindowclose.h"

class MessageFactoryMainWindow : public MessageFactory
{
public:
    enum MessageType
    {
        MAINWINDOW_OPEN,
        MAINWINDOW_TRYCLOSE,
        MAINWINDOW_CLOSE
    };
    MessageFactoryMainWindow();
    Message* produce(int type);
};

#endif // MESSAGEFACTORYMAINWINDOW_H
