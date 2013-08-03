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
    void calcCommonOutputMarkovStatus(QVector<double> PR);
    double calcTempOutputMarkovStatus(double time, QVector<double> input, QVector<double> subInput, int index);

private:
    void calcOutputMarkovStatusNormal();
    void calcOutputMarkovStatusCorrelate();
    void calcCommonOutputMarkovStatusNormal(QVector<double> PR);
    void calcCommonOutputMarkovStatusCorrelate(QVector<double> PR);
    double calcTempOutputMarkovStatusNormal1(double PS1, double PS2);
    double calcTempOutputMarkovStatusNormal2(double PS1, double PS2);
    double calcTempOutputMarkovStatusCorrelate1(double PS1, double PS2);
    double calcTempOutputMarkovStatusCorrelate2(double PS1, double PS2);
};

#endif // GOMARKOVOPERATOR1_H
