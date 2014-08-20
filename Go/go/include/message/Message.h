#ifndef MESSAGE_H
#define MESSAGE_H
#include "stable.h"
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
    void* _message;
};

#endif // MESSAGE_H
