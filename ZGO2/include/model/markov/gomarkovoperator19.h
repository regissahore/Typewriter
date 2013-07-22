#ifndef GOMARKOVOPERATOR19_H
#define GOMARKOVOPERATOR19_H
/**
 * 超压保护操作符。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "gomarkovoperator.h"

class GOMarkovOperator19 : public GOMarkovOperator
{
public:
    GOMarkovOperator19();
    ~GOMarkovOperator19();
    void calcOutputMarkovStatus(double time);
    double calcTempOutputMarkovStatus(double time, QVector<double> input, QVector<double> subInput, int index);
};

#endif // GOMARKOVOPERATOR1_H
