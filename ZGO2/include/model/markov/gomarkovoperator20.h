#ifndef GOMARKOVOPERATOR20_H
#define GOMARKOVOPERATOR20_H
/**
 * 非门控制。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "gomarkovoperator.h"

class GOMarkovOperator20 : public GOMarkovOperator
{
public:
    GOMarkovOperator20();
    ~GOMarkovOperator20();
    void calcOutputMarkovStatus(double time);
    void calcCommonOutputMarkovStatus(QVector<double> PR);
    double calcTempOutputMarkovStatus(double time, QVector<double> input, QVector<double> subInput, int index);
};

#endif // GOMARKOVOPERATOR1_H
