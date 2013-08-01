#ifndef GOMARKOVOPERATOR18_H
#define GOMARKOVOPERATOR18_H
/**
 * 备用门。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "gomarkovoperator.h"

class RungeKuttaMarkov18;

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
    RungeKuttaMarkov18 *_rungeKutta;
};

#endif // GOMARKOVOPERATOR1_H
