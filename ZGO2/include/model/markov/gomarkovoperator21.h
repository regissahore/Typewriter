#ifndef GOMARKOVOPERATOR21_H
#define GOMARKOVOPERATOR21_H
/**
 * 整体反馈。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "gomarkovoperator.h"

class GOMarkovOperator21 : public GOMarkovOperator
{
public:
    GOMarkovOperator21();
    ~GOMarkovOperator21();
    void calcOutputMarkovStatus(double time);
    double calcTempOutputMarkovStatus(double time, QVector<double> input, QVector<double> subInput, int index);
};

#endif // GOMARKOVOPERATOR1_H
