#ifndef GOMARKOVOPERATOR11A_H
#define GOMARKOVOPERATOR11A_H

#include "GoMarkovOperator.h"

class GoMarkovOperator11A : public GoMarkovOperator
{
public:
    GoMarkovOperator11A();
    ~GoMarkovOperator11A();
    void calcOutputMarkovStatus(double time);
    DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index);
};

#endif // GOMARKOVOPERATOR11A_H
