#ifndef GOMARKOVOPERATOR_H
#define GOMARKOVOPERATOR_H
/**
 * The operator model for GO Markov repairable system.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QVector>
#include "gooperator.h"

class GOMarkovStatus;

class GOMarkovOperator : public GOOperator
{
public:
    GOMarkovOperator();
    virtual ~GOMarkovOperator();
    GOMarkovStatus* markovStatus() const;
    QVector<GOMarkovStatus*>* markovOutputStatus() const;
    virtual void initMarkovStatus(double time, double c12 = 0.0);
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);

private:
    GOMarkovStatus *_markovStatus;
    QVector<GOMarkovStatus*> *_outputStatus;
};

#endif // GOMARKOVOPERATOR_H
