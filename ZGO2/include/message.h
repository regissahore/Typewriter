#ifndef MESSAGE_H
#define MESSAGE_H
/**
 * The basic structrue of message.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QString>
#include "identifieditem.h"
#include "typeditem.h"

class Message : public IdentifiedItem, public TypedItem
{
public:
    int paramInt;
    QString paramString;
    Message();
    ~Message();
    void* message() const;
    void setMessage(void* message);

protected:
    void* _message; /** The content of the message. */
};

#endif // MESSAGE_H
