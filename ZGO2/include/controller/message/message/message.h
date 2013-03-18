#ifndef MESSAGE_H
#define MESSAGE_H
/**
 * 基本的消息结构。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QString>
#include "identifieditem.h"
#include "nameditem.h"

class Message : public NamedItem, public IdentifiedItem
{
public:
    Message();
    ~Message();
    void* message() const;
    void setMessage(void* message);
    virtual QString toString();

protected:
    void* _message; /** 消息内容。 */
};

#endif // MESSAGE_H
