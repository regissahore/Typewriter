#ifndef MESSAGEEDITORTYPE_H
#define MESSAGEEDITORTYPE_H
/**
 * 当前编辑器类型。
 * 由编辑器发出。
 * 信息的内容为指向编辑器的指针，空指针代表没选中。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "controller/message.h"
#include "controller/definationeditortype.h"
#include "view/editorabstract.h"

class MessageEditorType : public Message
{
public:
    MessageEditorType();
    QString toString();
};

#endif // MESSAGEEDITORTYPE_H
