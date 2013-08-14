#ifndef GOMARKOVOPERATOR9A1_H
#define GOMARKOVOPERATOR9A1_H
/**
 * 有停工相关属性反馈操作符。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "gomarkovoperator9a.h"

class GOMarkovOperator9A1 : public GOMarkovOperator9A
{
public:
    GOMarkovOperator9A1();
    ~GOMarkovOperator9A1();
    void calcOutputMarkovStatus(double time);
    DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index);
};

#endif // GOMARKOVOPERATOR1_H
