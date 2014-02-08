#ifndef MESSAGEFACTORY_H
#define MESSAGEFACTORY_H
#include <QSharedPointer>
#include <QList>
#include "Message.h"

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
        TYPE_EDITOR_ANALYSIS_PROBABILITY,
        TYPE_EDITOR_ANALYSIS_PATH,
        TYPE_EDITOR_ANALYSIS_CUT,
        TYPE_EDITOR_COPY,
        TYPE_EDITOR_DELETE,
        TYPE_EDITOR_ZOOM_IN,
        TYPE_EDITOR_ZOOM_OUT,
        TYPE_EDITOR_SET_GLOBAL_FEEDBACK,
        TYPE_EDITOR_UNSET_GLOBAL_FEEDBBACK,
        TYPE_EDITOR_SHOW_PARAMETER,
        TYPE_EDITOR_HIDE_PARAMETER,
        TYPE_TOOL_SELECTION,
        TYPE_OUTPUT_CLEAR,
        TYPE_OUTPUT_TEXT,
        TYPE_OUTPUT_SAMELINE_TEXT,
        TYPE_OUTPUT_CORRECT,
        TYPE_OUTPUT_ERROR,
        TYPE_END
    };
    static QSharedPointer<Message> produce(int messageType);

private:
    static int _autoID;
};

#endif // MESSAGEFACTORY_H
