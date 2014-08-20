#ifndef GOMARKOVOPERATOR6_H
#define GOMARKOVOPERATOR6_H
#include "GoMarkovOperator.h"

class GoMarkovOperator6 : public GoMarkovOperator
{
public:
    GoMarkovOperator6();
    ~GoMarkovOperator6();
    virtual void calcQualitativeProbability();
    void calcOutputMarkovStatus(double time);
    void calcCommonOutputMarkovStatus(QVector<DoubleVector> PR);
    DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index);

private:
    void calcOutputMarkovStatusNormal();
    void calcOutputMarkovStatusCorrelate();
    void calcCommonOutputMarkovStatusNormal(DoubleVector PR);
    void calcCommonOutputMarkovStatusCorrelate(DoubleVector PR);
    DoubleVector calcTempOutputMarkovStatusNormal(DoubleVector PS1, DoubleVector PS2);
    DoubleVector calcTempOutputMarkovStatusCorrelate(DoubleVector PS1, DoubleVector PS2);
};

#endif // GOMARKOVOPERATOR1_H
