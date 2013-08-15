#ifndef GOMARKOVOPERATOR11A_H
#define GOMARKOVOPERATOR11A_H

#include "gomarkovoperator.h"

class GOMarkovOperator11A : public GOMarkovOperator
{
public:
    GOMarkovOperator11A();
    ~GOMarkovOperator11A();
    void calcOutputMarkovStatus(double time);
    DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index);
};

#endif // GOMARKOVOPERATOR11A_H
