#ifndef GOMARKOVOPERATOR13B_H
#define GOMARKOVOPERATOR13B_H
/**
 * 多路输入输出器"+"。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "gomarkovoperator13.h"

class GOMarkovOperator13B : public GOMarkovOperator13
{
public:
    GOMarkovOperator13B();
    ~GOMarkovOperator13B();
    void calcOutputMarkovStatus(double time);
    void calcCommonOutputMarkovStatus(QVector<DoubleVector> PR);
    DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index);
};

#endif // GOMARKOVOPERATOR13A_H
