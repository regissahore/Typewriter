#ifndef GOMARKOVOPERATOR13A_H
#define GOMARKOVOPERATOR13A_H
#include "GoMarkovOperator13.h"

class GoMarkovOperator13A : public GoMarkovOperator13
{
public:
    GoMarkovOperator13A();
    ~GoMarkovOperator13A();
    virtual void calcQualitativeProbability() override final;
    virtual void calcOutputMarkovStatus(double time) override final;
    virtual void calcCommonOutputMarkovStatus(QVector<DoubleVector> PR) override final;
    virtual DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index) override final;
};

#endif // GOMARKOVOPERATOR13A_H
