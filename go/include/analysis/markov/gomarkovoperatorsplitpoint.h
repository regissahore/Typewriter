#ifndef GOMARKOVOPERATORSPLITPOINT_H
#define GOMARKOVOPERATORSPLITPOINT_H

#include "GoMarkovOperator.h"

class GoMarkovOperatorSplitPoint : public GoMarkovOperator
{
public:
    GoMarkovOperatorSplitPoint();
    ~GoMarkovOperatorSplitPoint();
    void calcOutputMarkovStatus(double time);
    DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index);
};

#endif // GOMARKOVOPERATORSPLITPOINT_H
