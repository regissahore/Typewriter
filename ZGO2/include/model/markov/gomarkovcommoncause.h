#ifndef GOMARKOVCOMMONCAUSE_H
#define GOMARKOVCOMMONCAUSE_H
/**
 * The common cause for GO Markov repairable system.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QVector>
#include "domitem.h"

class GOMarkovOperator;

class GOMarkovCommonCause : DomItem
{
public:
    GOMarkovCommonCause();
    virtual ~GOMarkovCommonCause();
    QVector<GOMarkovOperator *> *operators() const;

protected:
    QVector<GOMarkovOperator*> *_operators;
};

#endif // GOMARKOVCOMMONCAUSE_H
