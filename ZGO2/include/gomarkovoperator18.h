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
    DoubleVector lambdaB1() const;
    void setLambdaB1(DoubleVector value);
    void calcOutputMarkovStatus(double time);
    DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index);
    GOMarkovOperator* copy();
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);

protected:
    RungeKuttaMarkov18 *_rungeKutta;
};

#endif // GOMARKOVOPERATOR1_H
