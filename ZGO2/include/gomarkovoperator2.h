#ifndef GOMARKOVOPERATOR2_H
#define GOMARKOVOPERATOR2_H
/**
 * 或门。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "gomarkovoperator.h"

class GOMarkovOperator2 : public GOMarkovOperator
{
public:
    GOMarkovOperator2();
    ~GOMarkovOperator2();
    void calcOutputMarkovStatus(double time);
    void calcCommonOutputMarkovStatus(QVector<double> PR);
    double calcTempOutputMarkovStatus(double time, QVector<double> input, QVector<double> subInput, int index);
};

#endif // GOMARKOVOPERATOR1_H
