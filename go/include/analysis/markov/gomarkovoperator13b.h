#ifndef GOMARKOVOPERATOR13B_H
#define GOMARKOVOPERATOR13B_H
#include "GoMarkovOperator13.h"

class GoMarkovOperator13B : public GoMarkovOperator13
{
public:
    GoMarkovOperator13B();
    ~GoMarkovOperator13B();
    virtual void calcQualitativeProbability();
    void calcOutputMarkovStatus(double time);
    void calcCommonOutputMarkovStatus(QVector<DoubleVector> PR);
    DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index);
};

#endif // GOMARKOVOPERATOR13A_H
