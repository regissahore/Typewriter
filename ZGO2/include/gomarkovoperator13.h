#ifndef GOMARKOVOPERATOR13_H
#define GOMARKOVOPERATOR13_H
/**
 * 多路输入输出器。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QVector>
#include "gomarkovoperator.h"

class GOMarkovOperator13 : public GOMarkovOperator
{
public:
    GOMarkovOperator13();
    virtual ~GOMarkovOperator13();
    void initRelation();
    QVector<QVector<int> >* relation();
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);
    void saveRelation(QDomDocument &document, QDomElement &root);
    bool tryOpenRelation(QDomElement &root);
    GOMarkovOperator* copy();

protected:
    QVector<QVector<int> > *_relation;
};

#endif // GOMARKOVOPERATOR13_H
