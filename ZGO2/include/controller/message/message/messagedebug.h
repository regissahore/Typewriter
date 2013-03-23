#ifndef MESSAGEDEBUG_H
#define MESSAGEDEBUG_H
/**
 * Send debug message.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "message.h"

class MessageDebug : public Message
{
public:
    MessageDebug();
    QString toString();
    QString debug() const;
    void setDebug(QString debug);
protected:
    QString _debug;
};

#endif // MESSAGEDEBUG_H
