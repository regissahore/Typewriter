#ifndef GOMARKOVOPERATOR9B1_H
#define GOMARKOVOPERATOR9B1_H

#include "GoMarkovOperator9b.h"

class GoMarkovOperator9B1 : public GoMarkovOperator9B
{
public:
    GoMarkovOperator9B1();
    virtual ~GoMarkovOperator9B1();
    void calcOutputMarkovStatus(double time);
    void calcCommonOutputMarkovStatus(QVector<DoubleVector> PR);
    DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index);
};

#endif // GOMARKOVOPERATOR9B1_H
