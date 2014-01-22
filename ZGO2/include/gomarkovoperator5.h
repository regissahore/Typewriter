#ifndef GOMARKOVOPERATOR5_H
#define GOMARKOVOPERATOR5_H
#include "gomarkovoperator.h"

class GOMarkovOperator5 : public GOMarkovOperator
{
public:
    GOMarkovOperator5();
    ~GOMarkovOperator5();
    void calcOutputMarkovStatus(double time);
};

#endif // GOMARKOVOPERATOR1_H
