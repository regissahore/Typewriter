#ifndef MESSAGEEDITORTYPE_H
#define MESSAGEEDITORTYPE_H
/**
 * 当前编辑器类型。
 * 由编辑器发出。
 * 返回信息中包括编辑器的编号。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "model/typeditem.h"
#include "controller/message.h"
#include "controller/definationeditortype.h"

class MessageEditorType : public Message, public TypedItem
{
public:
    class MessageContent
    {
    public:
        int index;
        MessageContent(int index)
        {
            this->index = index;
        }
    };
    MessageEditorType();
    ~MessageEditorType();
    QString toString();
    void setIndex(int index);
};

#endif // MESSAGEEDITORTYPE_H
