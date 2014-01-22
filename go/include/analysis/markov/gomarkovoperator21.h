#ifndef GOMARKOVOPERATOR21_H
#define GOMARKOVOPERATOR21_H
#include "GoMarkovOperator.h"

class GoMarkovOperator21 : public GoMarkovOperator
{
public:
    GoMarkovOperator21();
    ~GoMarkovOperator21();
    void calcOutputMarkovStatus(double time);
    DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index);
};

#endif // GOMARKOVOPERATOR1_H
