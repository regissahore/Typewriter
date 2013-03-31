#ifndef MESSAGEFACTORY_H
#define MESSAGEFACTORY_H
/**
 * The message factory.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QList>
#include "message.h"

class MessageFactory
{
public:
    enum MessageType
    {
        TYPE_DEBUG,
        TYPE_MAINWINDOW_OPEN,
        TYPE_MAINWINDOW_TRYCLOSE,
        TYPE_MAINWINDOW_CLOSE,
        TYPE_EDITOR_TYPE,
        TYPE_EDITOR_SELECTION,
        TYPE_EDITOR_NEW,
        TYPE_EDITOR_OPEN,
        TYPE_EDITOR_OPEN_EXIST,
        TYPE_EDITOR_CLOSE,
        TYPE_EDITOR_CLOSEALL,
        TYPE_EDITOR_SAVE,
        TYPE_EDITOR_SAVEALL,
        TYPE_EDITOR_SAVEAS,
        TYPE_EDITOR_ANALYSIS,
        TYPE_TOOL_SELECTION,
        TYPE_END
    };
    static Message* produce(int messageType);
    static QList<int> getMessageTypeList();
    static QString getMessageTypeName(int messageType);

private:
    static int _autoID;
};

#endif // MESSAGEFACTORY_H
