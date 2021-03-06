#ifndef GOMARKOVOPERATOR17_H
#define GOMARKOVOPERATOR17_H
#include "GoMarkovOperator.h"

class GoMarkovOperator17 : public GoMarkovOperator
{
public:
    GoMarkovOperator17();
    ~GoMarkovOperator17();
    virtual void calcQualitativeProbability() override final;
    virtual void calcOutputMarkovStatus(double time) override final;
    virtual void calcCommonOutputMarkovStatus(QVector<DoubleVector> PR) override final;
    virtual DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index) override final;

private:
    void calcOutputMarkovStatusNormal();
    void calcOutputMarkovStatusCorrelate();
    void calcCommonOutputMarkovStatusNormal(QVector<DoubleVector> PR);
    void calcCommonOutputMarkovStatusCorrelate(QVector<DoubleVector> PR);
    DoubleVector calcTempOutputMarkovStatusNormal1(DoubleVector PS1, DoubleVector PS2);
    DoubleVector calcTempOutputMarkovStatusNormal2(DoubleVector PS1, DoubleVector PS2);
    DoubleVector calcTempOutputMarkovStatusCorrelate1(DoubleVector PS1, DoubleVector PS2);
    DoubleVector calcTempOutputMarkovStatusCorrelate2(DoubleVector PS1, DoubleVector PS2);
};

#endif // GOMARKOVOPERATOR17_H
