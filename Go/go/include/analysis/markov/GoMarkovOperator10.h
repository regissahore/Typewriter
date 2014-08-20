#ifndef GOMARKOVOPERATOR10_H
#define GOMARKOVOPERATOR10_H
#include "GoMarkovOperator.h"

class GoMarkovOperator10 : public GoMarkovOperator
{
public:
    GoMarkovOperator10();
    ~GoMarkovOperator10();
    virtual void calcQualitativeProbability() override final;
    virtual void calcOutputMarkovStatus(double time) override final;
    virtual void calcCommonOutputMarkovStatus(QVector<DoubleVector> PR) override final;
    virtual DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index) override final;

private:
    void calcOutputMarkovStatusNormal();
    void calcOutputMarkovStatusCorrelate();
    void calcCommonOutputMarkovStatusNormal(DoubleVector PR);
    void calcCommonOutputMarkovStatusCorrelate(DoubleVector PR);
    DoubleVector calcTempOutputMarkovStatusNormal(QVector<DoubleVector> input);
    DoubleVector calcTempOutputMarkovStatusCorrelate(QVector<DoubleVector> input);
};

#endif // GOMARKOVOPERATOR1_H
