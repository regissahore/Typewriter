#ifndef GOMARKOVOPERATORSPLITPOINT_H
#define GOMARKOVOPERATORSPLITPOINT_H

#include "gomarkovoperator.h"

class GOMarkovOperatorSplitPoint : public GOMarkovOperator
{
public:
    GOMarkovOperatorSplitPoint();
    ~GOMarkovOperatorSplitPoint();
    void calcOutputMarkovStatus(double time);
    DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index);
};

#endif // GOMARKOVOPERATORSPLITPOINT_H
