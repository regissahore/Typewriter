#ifndef GOMARKOVOPERATOR22A_H
#define GOMARKOVOPERATOR22A_H
#include "gomarkovoperator22.h"

class GOMarkovOperator22A : public GOMarkovOperator22
{
public:
    GOMarkovOperator22A();
    ~GOMarkovOperator22A();
    void calcOutputMarkovStatus(double time);
    void calcCommonOutputMarkovStatus(QVector<DoubleVector> PR);
    DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index);
};

#endif // GOMARKOVOPERATOR1_H
