#ifndef GOMARKOVOPERATOR12A_H
#define GOMARKOVOPERATOR12A_H
/**
 * 状态分离器。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "gomarkovoperator.h"

class GOMarkovOperator12A : public GOMarkovOperator
{
public:
    GOMarkovOperator12A();
    ~GOMarkovOperator12A();
    void calcOutputMarkovStatus(double time);
    DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index);
};

#endif // GOMARKOVOPERATOR12A_H
