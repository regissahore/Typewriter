#ifndef GOMARKOVOPERATOR9A1_H
#define GOMARKOVOPERATOR9A1_H
#include "GoMarkovOperator9a.h"

class GoMarkovOperator9A1 : public GoMarkovOperator9A
{
public:
    GoMarkovOperator9A1();
    ~GoMarkovOperator9A1();
    void calcOutputMarkovStatus(double time);
    DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index);
};

#endif // GOMARKOVOPERATOR1_H
