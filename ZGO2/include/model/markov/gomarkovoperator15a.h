#ifndef GOMARKOVOPERATOR15A_H
#define GOMARKOVOPERATOR15A_H
/**
 * 对应门。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "gomarkovoperator.h"

class GOMarkovOperator15A : public GOMarkovOperator
{
public:
    GOMarkovOperator15A();
    ~GOMarkovOperator15A();
    void calcOutputMarkovStatus(double time);
    double calcTempOutputMarkovStatus(double time, QVector<double> input, QVector<double> subInput, int index);
};

#endif // GOMARKOVOPERATOR1_H
