#ifndef GOMARKOVOPERATOR17_H
#define GOMARKOVOPERATOR17_H
/**
 * 要求恢复已关断元件。有停工相关模式。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "gomarkovoperator.h"

class GOMarkovOperator17 : public GOMarkovOperator
{
public:
    GOMarkovOperator17();
    ~GOMarkovOperator17();
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

#endif // GOMARKOVOPERATOR17_H
