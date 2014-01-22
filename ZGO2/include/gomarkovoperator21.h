#ifndef GOMARKOVOPERATOR21_H
#define GOMARKOVOPERATOR21_H
#include "gomarkovoperator.h"

class GOMarkovOperator21 : public GOMarkovOperator
{
public:
    GOMarkovOperator21();
    ~GOMarkovOperator21();
    void calcOutputMarkovStatus(double time);
    DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index);
};

#endif // GOMARKOVOPERATOR1_H
