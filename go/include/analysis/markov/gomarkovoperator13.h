#ifndef GOMARKOVOPERATOR13_H
#define GOMARKOVOPERATOR13_H
#include <QVector>
#include "GoMarkovOperator.h"

class GoMarkovOperator13 : public GoMarkovOperator
{
public:
    GoMarkovOperator13();
    virtual ~GoMarkovOperator13();
    void initRelation();
    QVector<QVector<int> >* relation();
    void saveRelation(QDomDocument &document, QDomElement &root);
    bool tryOpenRelation(QDomElement &root);
    GoMarkovOperator* copy();
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);

protected:
    QVector<QVector<int> > *_relation;
};

#endif // GOMARKOVOPERATOR13_H
