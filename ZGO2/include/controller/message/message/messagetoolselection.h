#ifndef MESSAGETOOLSELECTION_H
#define MESSAGETOOLSELECTION_H
/**
 * 工具选择消息。
 * 发出者可能是菜单也可能是工具箱，由工具箱和编辑器接收。
 * 消息的内容永远为空，消息的类别为工具的类别。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "typeditem.h"
#include "message.h"
#include "definationtooltype.h"

class MessageToolSelection : public Message, public TypedItem
{
public:
    MessageToolSelection();
    QString toString();
};

#endif // MESSAGETOOLSELECTION_H
