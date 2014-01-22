#ifndef GOMARKOVOPERATOR15A_H
#define GOMARKOVOPERATOR15A_H
#include "gomarkovoperator.h"

class GOMarkovOperator15A : public GOMarkovOperator
{
public:
    GOMarkovOperator15A();
    ~GOMarkovOperator15A();
    void calcOutputMarkovStatus(double time);
    DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index);
};

#endif // GOMARKOVOPERATOR1_H
