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
    void calcCommonOutputMarkovStatus(QVector<double> PR);
    double calcTempOutputMarkovStatus(double time, QVector<double> input, QVector<double> subInput, int index);

private:
    void calcOutputMarkovStatusNormal();
    void calcOutputMarkovStatusCorrelate();
    void calcCommonOutputMarkovStatusNormal(double PR);
    void calcCommonOutputMarkovStatusCorrelate(double PR);
    double calcTempOutputMarkovStatusNormal(double PS1, double PS2);
    double calcTempOutputMarkovStatusCorrelate(double PS1, double PS2);
};

#endif // GOMARKOVOPERATOR1_H
