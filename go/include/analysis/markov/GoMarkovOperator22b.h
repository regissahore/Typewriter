#ifndef GOMARKOVOPERATOR22B_H
#define GOMARKOVOPERATOR22B_H
#include "GoMarkovOperator22.h"

class GoMarkovOperator22B : public GoMarkovOperator22
{
public:
    GoMarkovOperator22B();
    ~GoMarkovOperator22B();
    void calcOutputMarkovStatus(double time);
    void calcCommonOutputMarkovStatus(QVector<DoubleVector> PR);
    DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index);
};

#endif // GOMARKOVOPERATOR1_H
