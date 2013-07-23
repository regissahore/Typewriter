#ifndef GOMARKOVOPERATOR9A1_H
#define GOMARKOVOPERATOR9A1_H
/**
 * 有停工相关属性反馈操作符。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "gomarkovoperator9a.h"

class GOMarkovOperator9A1 : public GOMarkovOperator9A
{
public:
    GOMarkovOperator9A1();
    ~GOMarkovOperator9A1();
    void calcOutputMarkovStatus(double time);
    double calcTempOutputMarkovStatus(double time, QVector<double> input, QVector<double> subInput, int index);

protected:
    void calcOutputMarkovStatusNormal(double time);
    double calcTempOutputMarkovStatusNormal(double time);
    void calcOutputMarkovStatusBreakdown(double time);
    double calcTempOutputMarkovStatusBreakdown(double time);
};

#endif // GOMARKOVOPERATOR1_H
