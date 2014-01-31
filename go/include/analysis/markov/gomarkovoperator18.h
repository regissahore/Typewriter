#ifndef GOMARKOVOPERATOR18_H
#define GOMARKOVOPERATOR18_H
#include "GoMarkovOperator.h"

class RungeKuttaMarkov18;

class GoMarkovOperator18 : public GoMarkovOperator
{
public:
    GoMarkovOperator18();
    ~GoMarkovOperator18();
    virtual void calcQualitativeProbability();
    DoubleVector lambdaB1() const;
    void setLambdaB1(DoubleVector value);
    void calcOutputMarkovStatus(double time);
    DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index);
    GoMarkovOperator* copy();
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);

protected:
    RungeKuttaMarkov18 *_rungeKutta;
};

#endif // GOMARKOVOPERATOR1_H
