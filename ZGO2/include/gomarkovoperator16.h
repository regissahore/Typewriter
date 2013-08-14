#ifndef GOMARKOVOPERATOR16_H
#define GOMARKOVOPERATOR16_H
/**
 * 要求回复已导通元件。有停工相关模式。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "gomarkovoperator.h"

class GOMarkovOperator16 : public GOMarkovOperator
{
public:
    GOMarkovOperator16();
    ~GOMarkovOperator16();
    void calcOutputMarkovStatus(double time);
    void calcCommonOutputMarkovStatus(QVector<DoubleVector> PR);
    DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index);

private:
    void calcOutputMarkovStatusNormal();
    void calcOutputMarkovStatusCorrelate();
    void calcCommonOutputMarkovStatusNormal(QVector<DoubleVector> PR);
    void calcCommonOutputMarkovStatusCorrelate(QVector<DoubleVector> PR);
    DoubleVector calcTempOutputMarkovStatusNormal1(DoubleVector PS1, DoubleVector PS2);
    DoubleVector calcTempOutputMarkovStatusNormal2(DoubleVector PS1, DoubleVector PS2);
    DoubleVector calcTempOutputMarkovStatusCorrelate1(DoubleVector PS1, DoubleVector PS2);
    DoubleVector calcTempOutputMarkovStatusCorrelate2(DoubleVector PS1, DoubleVector PS2);
};

#endif // GOMARKOVOPERATOR1_H
