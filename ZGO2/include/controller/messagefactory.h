#ifndef MESSAGEFACTORY_H
#define MESSAGEFACTORY_H
/**
 * 生成消息。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QVector>
#include <QString>
#include "controller/message.h"

class MessageFactory
{
public:
    MessageFactory();
    Message* produce(int type);
    QString getMessageName(int type);
    QVector<QString> getMessageNameVector();

protected:
    virtual Message* produceMessage(int type);

private:
    static int _id; /** 利用工厂生成的消息的唯一编号。 */
};

#endif // MESSAGEFACTORY_H
