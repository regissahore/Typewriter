#ifndef GOMARKOVOPERATOR15A_H
#define GOMARKOVOPERATOR15A_H
#include "GoMarkovOperator.h"

class GoMarkovOperator15A : public GoMarkovOperator
{
public:
    GoMarkovOperator15A();
    ~GoMarkovOperator15A();
    void calcOutputMarkovStatus(double time);
    DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index);
};

#endif // GOMARKOVOPERATOR1_H
