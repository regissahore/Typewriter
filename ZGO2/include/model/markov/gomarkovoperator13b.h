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
    void calcCommonOutputMarkovStatus(QVector<double> PR);
    double calcTempOutputMarkovStatus(double time, QVector<double> input, QVector<double> subInput, int index);
};

#endif // GOMARKOVOPERATOR13A_H
