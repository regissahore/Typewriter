#ifndef GOMARKOVOPERATOR9A2_H
#define GOMARKOVOPERATOR9A2_H
#include "GoMarkovOperator9a.h"

class GoMarkovOperator9A2 : public GoMarkovOperator9A
{
public:
    GoMarkovOperator9A2();
    ~GoMarkovOperator9A2();
    void calcOutputMarkovStatus(double time);
    DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index);
};

#endif // GOMARKOVOPERATOR1_H
