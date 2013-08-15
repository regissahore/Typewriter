#ifndef GOMARKOVOPERATOR15B_H
#define GOMARKOVOPERATOR15B_H
/**
 * 工况并行运算。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "gomarkovoperator.h"

class GOMarkovOperator15B : public GOMarkovOperator
{
public:
    GOMarkovOperator15B();
    ~GOMarkovOperator15B();
    void calcOutputMarkovStatus(double time);
    DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index);
};

#endif // GOMARKOVOPERATOR1_H
