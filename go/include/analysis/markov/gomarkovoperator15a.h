#ifndef GOMARKOVOPERATOR15A_H
#define GOMARKOVOPERATOR15A_H
#include "GoMarkovOperator.h"

class GoMarkovOperator15A : public GoMarkovOperator
{
public:
    GoMarkovOperator15A();
    ~GoMarkovOperator15A();
    virtual void calcQualitativeProbability() override final;
    virtual void calcOutputMarkovStatus(double time) override final;
    virtual DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index) override final;
};

#endif // GOMARKOVOPERATOR1_H
