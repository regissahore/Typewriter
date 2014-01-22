#ifndef GOMARKOVOPERATOR13A_H
#define GOMARKOVOPERATOR13A_H
#include "gomarkovoperator13.h"

class GOMarkovOperator13A : public GOMarkovOperator13
{
public:
    GOMarkovOperator13A();
    ~GOMarkovOperator13A();
    void calcOutputMarkovStatus(double time);
    void calcCommonOutputMarkovStatus(QVector<DoubleVector> PR);
    DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index);
};

#endif // GOMARKOVOPERATOR13A_H
