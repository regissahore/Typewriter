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
    virtual void prepareNextCalculation(int count, double time);
protected:
    DoubleVector _lambdaS2Sum;
    DoubleVector _muS2Sum;
    DoubleVector lambdaS2;
    DoubleVector muS2;
};

#endif // GOMARKOVOPERATOR1_H
