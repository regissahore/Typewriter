#ifndef MESSAGECONTROLLER_H
#define MESSAGECONTROLLER_H
/**
 * 消息的控制管理。
 * 消息产生器发送的消息被监听器收到之后会立即执行，注意时序关系。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QMap>
#include <QVector>
#include <QString>
#include "message.h"

class MessageCreator;
class MessageListener;

class MessageController
{
public:
    MessageController();
    ~MessageController();
    void send(Message *message);
    void listen(QString messageName, MessageListener *listener);
    void release(QString messageName, MessageListener *listener);

protected:
    QMap<QString, int> *_messages; /** 储存已经注册的消息，数值为listeners的索引。 */
    QVector< QVector<MessageListener*> > *_listeners; /** 储存消息监听器。 */

private:
    int _autoID; /** 为消息准备的自动增长的ID。 */
};

#endif // MESSAGECONTROLLER_H
