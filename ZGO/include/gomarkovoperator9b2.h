#ifndef GOMARKOVOPERATOR9B2_H
#define GOMARKOVOPERATOR9B2_H

#include "gomarkovoperator9b.h"

class GOMarkovOperator9B2 : public GOMarkovOperator9B
{
public:
    GOMarkovOperator9B2();
    virtual ~GOMarkovOperator9B2();
    void calcOutputMarkovStatus(double time);
    void calcCommonOutputMarkovStatus(QVector<DoubleVector> PR);
    DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index);
};

#endif // GOMARKOVOPERATOR9B2_H
