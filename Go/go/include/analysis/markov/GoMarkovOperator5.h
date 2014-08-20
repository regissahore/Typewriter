#ifndef GOMARKOVOPERATOR5_H
#define GOMARKOVOPERATOR5_H
#include "GoMarkovOperator.h"

class GoMarkovOperator5 : public GoMarkovOperator
{
public:
    GoMarkovOperator5();
    ~GoMarkovOperator5();
    virtual void calcQualitativeProbability();
    void calcOutputMarkovStatus(double time);
};

#endif // GOMARKOVOPERATOR1_H
