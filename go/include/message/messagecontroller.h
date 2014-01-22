#ifndef MESSAGECONTROLLER_H
#define MESSAGECONTROLLER_H
#include <QMap>
#include <QVector>
#include <QString>
#include "Message.h"

class MessageCreator;
class MessageListener;

class MessageController
{
public:
    MessageController();
    virtual ~MessageController();
    void send(QSharedPointer<Message> message);
    void listen(int messageType, MessageListener *listener);
    void release(int messageType, MessageListener *listener);

protected:
    QMap<int, int> *_messages; /** 储存已经注册的消息，数值为listeners的索引。 */
    QVector< QVector<MessageListener*> > *_listeners; /** 储存消息监听器。 */
};

#endif // MESSAGECONTROLLER_H
