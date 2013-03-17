#ifndef MESSAGEEDITORSELECTION_H
#define MESSAGEEDITORSELECTION_H
/**
 * 编辑器选择内容的消息。
 * 由编辑器发出。
 * 消息的内容为被选择项的地址，空指针代表没选中。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "model/gooperator.h"
#include "model/gosignal.h"
#include "controller/message.h"
#include "controller/definationeditorselectiontype.h"

class MessageEditorSelection : public Message, public TypedItem
{
public:
    MessageEditorSelection();
    QString toString();
};

#endif // MESSAGEEDITORSELECTION_H
