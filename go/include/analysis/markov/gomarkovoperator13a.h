#ifndef GOMARKOVOPERATOR13A_H
#define GOMARKOVOPERATOR13A_H
#include "GoMarkovOperator13.h"

class GoMarkovOperator13A : public GoMarkovOperator13
{
public:
    GoMarkovOperator13A();
    ~GoMarkovOperator13A();
    void calcOutputMarkovStatus(double time);
    void calcCommonOutputMarkovStatus(QVector<DoubleVector> PR);
    DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index);
};

#endif // GOMARKOVOPERATOR13A_H
