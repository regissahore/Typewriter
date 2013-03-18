#include "messagefactorymainwindow.h"

/**
 * 构造函数。
 */
MessageFactoryMainWindow::MessageFactoryMainWindow()
{
}

/**
 * 生成主窗口的消息。
 * @param type 消息类型。
 */
Message* MessageFactoryMainWindow::produce(int type)
{
    Message* message = 0L;
    switch (type)
    {
    case MAINWINDOW_OPEN:
        message = new MessageMainWindowOpen();
        break;
    case MAINWINDOW_TRYCLOSE:
        message = new MessageMainWindowTryClose();
        break;
    case MAINWINDOW_CLOSE:
        message = new MessageMainWindowClose();
        break;
    }
    return message;
}
