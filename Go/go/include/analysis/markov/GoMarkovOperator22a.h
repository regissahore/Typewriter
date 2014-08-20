#ifndef GOMARKOVOPERATOR22A_H
#define GOMARKOVOPERATOR22A_H
#include "GoMarkovOperator22.h"

class GoMarkovOperator22A : public GoMarkovOperator22
{
public:
    GoMarkovOperator22A();
    ~GoMarkovOperator22A();
    void calcQualitativeProbability() override;
    void calcOutputMarkovStatus(double time) override;
    void calcCommonOutputMarkovStatus(QVector<DoubleVector> PR) override;
    DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index) override;
};

#endif // GOMARKOVOPERATOR1_H
