#ifndef GOMARKOVOPERATOR5_H
#define GOMARKOVOPERATOR5_H
/**
 * 单信号发生器。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "gomarkovoperator.h"

class GOMarkovOperator5 : public GOMarkovOperator
{
public:
    GOMarkovOperator5();
    ~GOMarkovOperator5();
    void calcOutputMarkovStatus(double time);
};

#endif // GOMARKOVOPERATOR1_H
