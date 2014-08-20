#include <QObject>
#include "MessageFactory.h"
using namespace std;

int MessageFactory::_autoID = 0;

QSharedPointer<Message> MessageFactory::produce(int messageType)
{
    QSharedPointer<Message> message = QSharedPointer<Message>(new Message());
    message->setType(messageType);
    message->setId(_autoID++);
    return message;
}
