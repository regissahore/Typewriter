#ifndef GOMARKOVOPERATOR15B_H
#define GOMARKOVOPERATOR15B_H
#include "GoMarkovOperator.h"

class GoMarkovOperator15B : public GoMarkovOperator
{
public:
    GoMarkovOperator15B();
    ~GoMarkovOperator15B();
    void calcOutputMarkovStatus(double time);
    DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index);
};

#endif // GOMARKOVOPERATOR1_H
