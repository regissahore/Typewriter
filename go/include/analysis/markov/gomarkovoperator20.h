#ifndef GOMARKOVOPERATOR20_H
#define GOMARKOVOPERATOR20_H
#include "GoMarkovOperator.h"

class GoMarkovOperator20 : public GoMarkovOperator
{
public:
    GoMarkovOperator20();
    ~GoMarkovOperator20();
    void calcOutputMarkovStatus(double time);
    void calcCommonOutputMarkovStatus(QVector<DoubleVector> PR);
    DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index);
};

#endif // GOMARKOVOPERATOR1_H
