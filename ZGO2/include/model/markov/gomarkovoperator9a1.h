#ifndef GOMARKOVOPERATOR9A1_H
#define GOMARKOVOPERATOR9A1_H
/**
 * 有停工相关属性反馈操作符。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "gomarkovoperator9a.h"

class GOMarkovOperator9A1 : public GOMarkovOperator9A
{
public:
    GOMarkovOperator9A1();
    ~GOMarkovOperator9A1();
    void calcOutputMarkovStatus(double time);
    double calcTempOutputMarkovStatus(double time, QVector<double> input, QVector<double> subInput, int index);

protected:
    void calcOutputMarkovStatusNormal(double time);
    double calcTempOutputMarkovStatusNormal(double time);
    void calcOutputMarkovStatusBreakdown(double time);
    double calcTempOutputMarkovStatusBreakdown(double time);

private:
    double calcNormalProbability(double time, double lambda1, double lambda2, double mu1, double mu2);
    double func0(double t, double x0, double x1, double x2, double lambda1, double lambda2, double mu1, double mu2);
    double func1(double t, double x0, double x1, double lambda1, double mu1);
    double func2(double t, double x0, double x2, double lambda2, double mu2);
    double _rk0;
    double _rk1;
    double _rk2;
    double _rkt;
};

#endif // GOMARKOVOPERATOR1_H
