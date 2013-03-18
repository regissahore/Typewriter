#ifndef MESSAGEFACTORY_H
#define MESSAGEFACTORY_H
/**
 * 生成消息。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QVector>
#include <QString>
#include "message.h"

class MessageFactory
{
public:
    MessageFactory();
    virtual Message* produce(int type);
    QString getMessageName(int type);
    QVector<QString> getMessageNameVector();
};

#endif // MESSAGEFACTORY_H
