#ifndef GOMARKOVOPERATOR9A2_H
#define GOMARKOVOPERATOR9A2_H
/**
 * 无停工相关属性反馈操作符。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "gomarkovoperator9a.h"

class GOMarkovOperator9A2 : public GOMarkovOperator9A
{
public:
    GOMarkovOperator9A2();
    ~GOMarkovOperator9A2();
    void calcOutputMarkovStatus(double time);
    DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index);
};

#endif // GOMARKOVOPERATOR1_H
