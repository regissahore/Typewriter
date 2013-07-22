#ifndef GOMARKOVOPERATOR22A_H
#define GOMARKOVOPERATOR22A_H
/**
 * 两状态单元。有两故障和与输入信号有停工相关两种模式。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "gomarkovoperator22.h"

class GOMarkovOperator22A : public GOMarkovOperator22
{
public:
    GOMarkovOperator22A();
    ~GOMarkovOperator22A();
    void calcOutputMarkovStatus(double time);
    void calcCommonOutputMarkovStatus(QVector<double> PR);
    double calcTempOutputMarkovStatus(double time, QVector<double> input, QVector<double> subInput, int index);
};

#endif // GOMARKOVOPERATOR1_H
