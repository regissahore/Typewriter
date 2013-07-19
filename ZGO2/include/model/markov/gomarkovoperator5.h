#ifndef GOMARKOVOPERATOR5_H
#define GOMARKOVOPERATOR5_H
/**
 * 两状态单元。有两故障和与输入信号有停工相关两种模式。
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
