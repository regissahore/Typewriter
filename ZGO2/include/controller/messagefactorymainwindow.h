#ifndef MESSAGEFACTORYMAINWINDOW_H
#define MESSAGEFACTORYMAINWINDOW_H
/**
 * 生成主窗口的消息。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "controller/messagefactory.h"

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

protected:
    Message* produceMessage(int type);
};

/**
 * 主窗口初始化完成事件，没有参数。
 * 由主窗口发出，任何窗体都可以监听。
 */
class MessageMainWindowOpen : public Message
{
public:
    MessageMainWindowOpen()
    {
        this->setName("MainWindow_Open");
    }
};

/**
 * 主窗口尝试关闭的消息，没有参数。
 * 由和关闭主窗口相关的操作产生，编辑器监听。
 */
class MessageMainWindowTryClose : public Message
{
public:
    MessageMainWindowTryClose()
    {
        this->setName("MainWindow_TryClose");
    }
};

/**
 * 主窗口直接关闭的消息，没有参数。
 * 由编辑器发出，主窗口监听。
 */
class MessageMainWindowClose : public Message
{
public:
    MessageMainWindowClose()
    {
        this->setName("MainWindow_Close");
    }
};

#endif // MESSAGEFACTORYMAINWINDOW_H
