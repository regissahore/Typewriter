#ifndef GOIOMODEL_H
#define GOIOMODEL_H
/**
 * 用于GO操作符的输入输出。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QVector>
#include "gosignal.h"
#include "domitem.h"

class GOIOModel : public DomItem
{
public:
    GOIOModel();
    int number() const;
    void setNumber(int num);
    void add(GOSignal* signal);
    void set(int index, GOSignal* signal);
    void remove(int index);
    QVector<GOSignal*>* signal() const;
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);

private:
    QVector<GOSignal*> *_signal; /** 信号流的集合。 */
};

#endif // GOIOMODEL_H
