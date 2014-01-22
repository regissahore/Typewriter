#ifndef GOMARKOVOPERATOR9A1_H
#define GOMARKOVOPERATOR9A1_H
#include "gomarkovoperator9a.h"

class GOMarkovOperator9A1 : public GOMarkovOperator9A
{
public:
    GOMarkovOperator9A1();
    ~GOMarkovOperator9A1();
    void calcOutputMarkovStatus(double time);
    DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index);
};

#endif // GOMARKOVOPERATOR1_H
