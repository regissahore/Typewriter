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
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);
    virtual void initMarkovStatus(double time, double c12 = 0.0);
    virtual void calcOutputMarkovStatus(double time);
    virtual double calcTempOutputMarkovStatus(double time, QVector<double> input, QVector<double> subInput);

protected:
    GOMarkovStatus *_markovStatus;
    QVector<GOMarkovStatus*> *_outputStatus;
    GOMarkovOperator* getPrevOperator(int index = 0);
    GOMarkovStatus* getPrevMarkovStatus(int index = 0);
    void initOutputMarkovStatus();
};

#endif // GOMARKOVOPERATOR_H
