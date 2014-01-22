#ifndef GOMARKOVOPERATOR2_H
#define GOMARKOVOPERATOR2_H
#include "gomarkovoperator.h"

class GOMarkovOperator2 : public GOMarkovOperator
{
public:
    GOMarkovOperator2();
    ~GOMarkovOperator2();
    void calcOutputMarkovStatus(double time);
    void calcCommonOutputMarkovStatus(QVector<DoubleVector> PR);
    DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index);
};

#endif // GOMARKOVOPERATOR1_H
