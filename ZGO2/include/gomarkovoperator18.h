#ifndef GOMARKOVOPERATOR18_H
#define GOMARKOVOPERATOR18_H
/**
 * 备用门。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "gomarkovoperator.h"

class GOMarkovOperator18 : public GOMarkovOperator
{
public:
    GOMarkovOperator18();
    ~GOMarkovOperator18();
    double lambdaB1() const;
    void setLambdaB1(double value);
    void calcOutputMarkovStatus(double time);
    double calcTempOutputMarkovStatus(double time, QVector<double> input, QVector<double> subInput, int index);
    GOMarkovOperator* copy();
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);

protected:
    double _lambdaB1;

private:
    double calcNormalProbability(double time, double lambda1, double lambda2, double mu1, double mu2);
    double func0(double t, double x0, double x1, double x2, double x3, double lambda1, double lambda2, double mu1, double mu2);
    double func1(double t, double x0, double x1, double x2, double x3, double lambda1, double lambda2, double mu1, double mu2);
    double func2(double t, double x0, double x1, double x2, double x3, double lambda1, double lambda2, double mu1, double mu2);
    double func3(double t, double x0, double x1, double x2, double x3, double lambda1, double lambda2, double mu1, double mu2);
    double _rk0;
    double _rk1;
    double _rk2;
    double _rk3;
    double _rkt;
};

#endif // GOMARKOVOPERATOR1_H
