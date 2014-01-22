#ifndef GOMARKOVOPERATOR10_H
#define GOMARKOVOPERATOR10_H
#include "GoMarkovOperator.h"

class GoMarkovOperator10 : public GoMarkovOperator
{
public:
    GoMarkovOperator10();
    ~GoMarkovOperator10();
    void calcOutputMarkovStatus(double time);
    void calcCommonOutputMarkovStatus(QVector<DoubleVector> PR);
    DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index);

private:
    void calcOutputMarkovStatusNormal();
    void calcOutputMarkovStatusCorrelate();
    void calcCommonOutputMarkovStatusNormal(DoubleVector PR);
    void calcCommonOutputMarkovStatusCorrelate(DoubleVector PR);
    DoubleVector calcTempOutputMarkovStatusNormal(QVector<DoubleVector> input);
    DoubleVector calcTempOutputMarkovStatusCorrelate(QVector<DoubleVector> input);
};

#endif // GOMARKOVOPERATOR1_H
