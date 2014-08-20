#ifndef GOMARKOVOPERATOR9B2_H
#define GOMARKOVOPERATOR9B2_H

#include "GoMarkovOperator9b.h"

class GoMarkovOperator9B2 : public GoMarkovOperator9B
{
public:
    GoMarkovOperator9B2();
    virtual ~GoMarkovOperator9B2();
    void calcOutputMarkovStatus(double time);
    void calcCommonOutputMarkovStatus(QVector<DoubleVector> PR);
    DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index);
};

#endif // GOMARKOVOPERATOR9B2_H
