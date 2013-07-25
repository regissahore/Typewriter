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
    double calcTempOutputMarkovStatus(double time, QVector<double> input, QVector<double> subInput, int index);
    bool errorDetect(Messager *messager);
};

#endif // GOMARKOVOPERATOR12A_H
