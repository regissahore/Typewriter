#ifndef GOMARKOVOPERATOR1_H
#define GOMARKOVOPERATOR1_H
/**
 * 两状态单元。有两故障和与输入信号有停工相关两种模式。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "gomarkovoperator.h"

class GOMarkovOperator1 : public GOMarkovOperator
{
public:
    GOMarkovOperator1();
    ~GOMarkovOperator1();
    void calcOutputMarkovStatus(double time);
    DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index);

private:
    void calcOutputMarkovStatusNormal();
    void calcOutputMarkovStatusCorrelate();
    DoubleVector calcTempOutputMarkovStatusNormal(DoubleVector PS);
    DoubleVector calcTempOutputMarkovStatusCorrelate(DoubleVector PS);
};

#endif // GOMARKOVOPERATOR1_H
