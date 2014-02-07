#ifndef GOMARKOVOPERATOR11A_H
#define GOMARKOVOPERATOR11A_H

#include "GoMarkovOperator.h"

class GoMarkovOperator11A : public GoMarkovOperator
{
public:
    GoMarkovOperator11A();
    ~GoMarkovOperator11A();
    virtual void calcQualitativeProbability() override final;
    virtual void calcOutputMarkovStatus(double time) override final;
    virtual DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index) override final;
};

#endif // GOMARKOVOPERATOR11A_H
