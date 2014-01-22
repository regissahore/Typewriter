#ifndef GOMARKOVOPERATOR22B_H
#define GOMARKOVOPERATOR22B_H
#include "gomarkovoperator22.h"

class GOMarkovOperator22B : public GOMarkovOperator22
{
public:
    GOMarkovOperator22B();
    ~GOMarkovOperator22B();
    void calcOutputMarkovStatus(double time);
    void calcCommonOutputMarkovStatus(QVector<DoubleVector> PR);
    DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index);
};

#endif // GOMARKOVOPERATOR1_H
