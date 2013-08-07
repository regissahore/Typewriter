#ifndef GOMARKOVOPERATOR9B2_H
#define GOMARKOVOPERATOR9B2_H

#include "gomarkovoperator9b.h"

class GOMarkovOperator9B2 : public GOMarkovOperator9B
{
public:
    GOMarkovOperator9B2();
    virtual ~GOMarkovOperator9B2();
    void calcOutputMarkovStatus(double time);
    void calcCommonOutputMarkovStatus(QVector<double> PR);
    double calcTempOutputMarkovStatus(double time, QVector<double> input, QVector<double> subInput, int index);
};

#endif // GOMARKOVOPERATOR9B2_H
