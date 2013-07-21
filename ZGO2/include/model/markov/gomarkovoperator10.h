#ifndef GOMARKOVOPERATOR10_H
#define GOMARKOVOPERATOR10_H
/**
 * 与门。有停工相关模式。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "gomarkovoperator.h"

class GOMarkovOperator10 : public GOMarkovOperator
{
public:
    GOMarkovOperator10();
    ~GOMarkovOperator10();
    void calcOutputMarkovStatus(double time);
    void calcCommonOutputMarkovStatus(double PR);
    double calcTempOutputMarkovStatus(double time, QVector<double> input, QVector<double> subInput);

private:
    bool _isBreakdownCorrelate;
    void calcOutputMarkovStatusNormal();
    void calcOutputMarkovStatusCorrelate();
    void calcCommonOutputMarkovStatusNormal(double PR);
    void calcCommonOutputMarkovStatusCorrelate(double PR);
    double calcTempOutputMarkovStatusNormal(QVector<double> input);
    double calcTempOutputMarkovStatusCorrelate(QVector<double> input);
};

#endif // GOMARKOVOPERATOR1_H
