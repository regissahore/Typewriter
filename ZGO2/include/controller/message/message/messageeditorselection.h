#ifndef MESSAGEEDITORSELECTION_H
#define MESSAGEEDITORSELECTION_H
/**
 * The message sent by editor.
 * The content of the message is the pointer to the selected item, it is null when nothing is selected.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "itemgooperator.h"
#include "gosignal.h"
#include "message.h"
#include "definationeditorselectiontype.h"

class MessageEditorSelection : public Message, public TypedItem
{
public:
    MessageEditorSelection();
    QString toString();
};

#endif // MESSAGEEDITORSELECTION_H
