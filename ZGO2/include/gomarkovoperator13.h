#ifndef GOMARKOVOPERATOR13_H
#define GOMARKOVOPERATOR13_H
#include <QVector>
#include "gomarkovoperator.h"

class GOMarkovOperator13 : public GOMarkovOperator
{
public:
    GOMarkovOperator13();
    virtual ~GOMarkovOperator13();
    void initRelation();
    QVector<QVector<int> >* relation();
    void saveRelation(QDomDocument &document, QDomElement &root);
    bool tryOpenRelation(QDomElement &root);
    GOMarkovOperator* copy();
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);

protected:
    QVector<QVector<int> > *_relation;
};

#endif // GOMARKOVOPERATOR13_H
