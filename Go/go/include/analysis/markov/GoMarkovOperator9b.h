#ifndef GOMARKOVOPERATOR9B_H
#define GOMARKOVOPERATOR9B_H
#include "GoMarkovOperator9.h"

class GoMarkovOperator9B : public GoMarkovOperator9
{
public:
    GoMarkovOperator9B();
    ~GoMarkovOperator9B();
    virtual void calcQualitativeProbability();
    virtual void initCalculation(double interval);
    virtual void prepareSum() override;
protected:
    DoubleVector _lambdaS2Sum;
    DoubleVector _muS2Sum;
    DoubleVector lambdaS2;
    DoubleVector muS2;
    int _sumCount2;
};

#endif // GOMARKOVOPERATOR1_H
