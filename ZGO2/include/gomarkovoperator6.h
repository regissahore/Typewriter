#ifndef GOMARKOVOPERATOR6_H
#define GOMARKOVOPERATOR6_H
/**
 * 有条件而导通的元器件。有停工相关模式。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "gomarkovoperator.h"

class GOMarkovOperator6 : public GOMarkovOperator
{
public:
    GOMarkovOperator6();
    ~GOMarkovOperator6();
    void calcOutputMarkovStatus(double time);
    void calcCommonOutputMarkovStatus(QVector<DoubleVector> PR);
    DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index);

private:
    void calcOutputMarkovStatusNormal();
    void calcOutputMarkovStatusCorrelate();
    void calcCommonOutputMarkovStatusNormal(DoubleVector PR);
    void calcCommonOutputMarkovStatusCorrelate(DoubleVector PR);
    DoubleVector calcTempOutputMarkovStatusNormal(DoubleVector PS1, DoubleVector PS2);
    DoubleVector calcTempOutputMarkovStatusCorrelate(DoubleVector PS1, DoubleVector PS2);
};

#endif // GOMARKOVOPERATOR1_H
