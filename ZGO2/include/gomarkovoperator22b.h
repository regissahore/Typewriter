#ifndef GOMARKOVOPERATOR22B_H
#define GOMARKOVOPERATOR22B_H
/**
 *
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "gomarkovoperator22.h"

class GOMarkovOperator22B : public GOMarkovOperator22
{
public:
    GOMarkovOperator22B();
    ~GOMarkovOperator22B();
    void calcOutputMarkovStatus(double time);
    void calcCommonOutputMarkovStatus(QVector<double> PR);
    double calcTempOutputMarkovStatus(double time, QVector<double> input, QVector<double> subInput, int index);
};

#endif // GOMARKOVOPERATOR1_H
