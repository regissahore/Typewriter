#ifndef GOMARKOVOPERATOR13B_H
#define GOMARKOVOPERATOR13B_H
#include "GoMarkovOperator13.h"

class GoMarkovOperator13B : public GoMarkovOperator13
{
public:
    GoMarkovOperator13B();
    ~GoMarkovOperator13B();
    virtual void calcQualitativeProbability() override final;
    virtual void calcOutputMarkovStatus(double time) override final;
    virtual void calcCommonOutputMarkovStatus(QVector<DoubleVector> PR) override final;
    virtual DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index) override final;
};

#endif // GOMARKOVOPERATOR13A_H
