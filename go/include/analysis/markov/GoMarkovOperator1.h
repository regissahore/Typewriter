#ifndef GOMARKOVOPERATOR1_H
#define GOMARKOVOPERATOR1_H
#include "GoMarkovOperator.h"

class GoMarkovOperator1 : public GoMarkovOperator
{
public:
    GoMarkovOperator1();
    ~GoMarkovOperator1();
    virtual void calcQualitativeProbability() override final;
    virtual void calcOutputMarkovStatus(double time) override final;
    virtual DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index) override final;

private:
    void calcOutputMarkovStatusNormal();
    void calcOutputMarkovStatusCorrelate();
    DoubleVector calcTempOutputMarkovStatusNormal(DoubleVector PS);
    DoubleVector calcTempOutputMarkovStatusCorrelate(DoubleVector PS);
};

#endif // GOMARKOVOPERATOR1_H
