#ifndef GOMARKOVOPERATOR9A_H
#define GOMARKOVOPERATOR9A_H
#include "GoMarkovOperator9.h"

class GoMarkovOperator9A : public GoMarkovOperator9
{
public:
    GoMarkovOperator9A();
    virtual ~GoMarkovOperator9A();
    virtual void calcQualitativeProbability();
};

#endif // GOMARKOVOPERATOR9A_H
