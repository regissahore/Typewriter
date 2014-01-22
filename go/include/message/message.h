#ifndef MESSAGE_H
#define MESSAGE_H
#include <QString>
#include <QSharedPointer>
#include "IdentifiedItem.h"
#include "TypedItem.h"

class Message : public IdentifiedItem, public TypedItem
{
public:
    int paramInt;
    QString paramString;
    Message();
    virtual ~Message();
    void* message() const;
    void setMessage(void* message);

protected:
    void* _message; /** The content of the message. */
};

#endif // MESSAGE_H
