#ifndef GOMARKOVOPERATOR9B1_H
#define GOMARKOVOPERATOR9B1_H

#include "gomarkovoperator9b.h"

class GOMarkovOperator9B1 : public GOMarkovOperator9B
{
public:
    GOMarkovOperator9B1();
    virtual ~GOMarkovOperator9B1();
    void calcOutputMarkovStatus(double time);
    void calcCommonOutputMarkovStatus(QVector<double> PR);
    double calcTempOutputMarkovStatus(double time, QVector<double> input, QVector<double> subInput, int index);
};

#endif // GOMARKOVOPERATOR9B1_H
