#ifndef GOMARKOVOPERATOR9B1_H
#define GOMARKOVOPERATOR9B1_H

#include "gomarkovoperator9b.h"

class GOMarkovOperator9B1 : public GOMarkovOperator9B
{
public:
    GOMarkovOperator9B1();
    virtual ~GOMarkovOperator9B1();
    void calcOutputMarkovStatus(double time);
    void calcCommonOutputMarkovStatus(QVector<DoubleVector> PR);
    DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index);
};

#endif // GOMARKOVOPERATOR9B1_H
