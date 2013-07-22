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
    void initOutputMarkovStatus();
    void calcOutputMarkovStatus(double time);
    double calcTempOutputMarkovStatus(double time, QVector<double> input, QVector<double> subInput, int index);
};

#endif // GOMARKOVOPERATOR1_H
