#ifndef GOMARKOVOPERATOR2_H
#define GOMARKOVOPERATOR2_H
#include "GoMarkovOperator.h"

class GoMarkovOperator2 : public GoMarkovOperator
{
public:
    GoMarkovOperator2();
    ~GoMarkovOperator2();
    virtual void calcQualitativeProbability();
    void calcOutputMarkovStatus(double time);
    void calcCommonOutputMarkovStatus(QVector<DoubleVector> PR);
    DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index);
};

#endif // GOMARKOVOPERATOR1_H
