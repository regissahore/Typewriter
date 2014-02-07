#include <QObject>
#include "MessageFactory.h"
using namespace std;

int MessageFactory::_autoID = 0;

QSharedPointer<Message> MessageFactory::produce(int messageType)
{
    QSharedPointer<Message> message = QSharedPointer<Message>(new Message());
    message->setType(messageType);
    message->setId(_autoID++);
    return message;
}

QList<int> MessageFactory::getMessageTypeList()
{
    QList<int> list;
    for (int i = 0; i != TYPE_END; ++i)
    {
        list.push_back(i);
    }
    return list;
}

QString MessageFactory::getMessageTypeName(int messageType)
{
    switch (messageType)
    {
    case TYPE_DEBUG:
        return QObject::tr("TYPE_DEBUG");
    case TYPE_MAINWINDOW_OPEN:
        return QObject::tr("TYPE_MAINWINDOW_OPEN");
    case TYPE_EDITOR_OPEN_EXIST:
        return QObject::tr("TYPE_EDITOR_OPEN_EXIST");
    case TYPE_MAINWINDOW_TRYCLOSE:
        return QObject::tr("TYPE_MAINWINDOW_TRYCLOSE");
    case TYPE_MAINWINDOW_CLOSE:
        return QObject::tr("TYPE_MAINWINDOW_CLOSE");
    case TYPE_EDITOR_TYPE:
        return QObject::tr("TYPE_EDITOR_TYPE");
    case TYPE_EDITOR_SELECTION:
        return QObject::tr("TYPE_EDITOR_SELECTION");
    case TYPE_EDITOR_NEW:
        return QObject::tr("TYPE_EDITOR_NEW");
    case TYPE_EDITOR_CLOSE:
        return QObject::tr("TYPE_EDITOR_CLOSE");
    case TYPE_EDITOR_CLOSEALL:
        return QObject::tr("TYPE_EDITOR_CLOSEALL");
    case TYPE_EDITOR_SAVE:
        return QObject::tr("TYPE_EDITOR_SAVE");
    case TYPE_EDITOR_SAVEALL:
        return QObject::tr("TYPE_EDITOR_SAVEALL");
    case TYPE_EDITOR_SAVEAS:
        return QObject::tr("TYPE_EDITOR_SAVEAS");
    case TYPE_EDITOR_ANALYSIS_PROBABILITY:
        return QObject::tr("TYPE_EDITOR_ANALYSIS");
    case TYPE_TOOL_SELECTION:
        return QObject::tr("TYPE_TOOL_SELECTION");
    case TYPE_OUTPUT_CLEAR:
        return QObject::tr("TYPE_OUTPUT_CLEAR");
    case TYPE_OUTPUT_TEXT:
        return QObject::tr("TYPE_OUTPUT_TEXT");
    case TYPE_OUTPUT_SAMELINE_TEXT:
        return QObject::tr("TYPE_OUTPUT_SAMELINE_TEXT");
    case TYPE_OUTPUT_CORRECT:
        return QObject::tr("TYPE_OUTPUT_CORRECT");
    case TYPE_OUTPUT_ERROR:
        return QObject::tr("TYPE_OUTPUT_ERROR");
    default:
        return QObject::tr("TYPE_UNDEFINED");
    }
}

