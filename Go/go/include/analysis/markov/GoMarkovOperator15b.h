#ifndef GOMARKOVOPERATOR15B_H
#define GOMARKOVOPERATOR15B_H
#include "GoMarkovOperator.h"

class GoMarkovOperator15B : public GoMarkovOperator
{
public:
    GoMarkovOperator15B();
    ~GoMarkovOperator15B();
    virtual void calcQualitativeProbability() override final;
    virtual void calcOutputMarkovStatus(double time) override final;
    virtual DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index) override final;
};

#endif // GOMARKOVOPERATOR1_H
