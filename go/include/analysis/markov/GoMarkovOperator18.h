#ifndef GOMARKOVOPERATOR18_H
#define GOMARKOVOPERATOR18_H
#include "GoMarkovOperator.h"

class RungeKuttaMarkov18;

class GoMarkovOperator18 : public GoMarkovOperator
{
public:
    GoMarkovOperator18();
    ~GoMarkovOperator18();
    virtual void calcQualitativeProbability() override;
    DoubleVector lambdaB1() const;
    void setLambdaB1(DoubleVector value);
    virtual void calcOutputMarkovStatus(double time) override;
    virtual DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index) override;
    virtual GoMarkovOperator* copy() override;
    virtual void save(QDomDocument &document, QDomElement &root) override;
    virtual bool tryOpen(QDomElement &root) override;

protected:
    RungeKuttaMarkov18 *_rungeKutta;
};

#endif // GOMARKOVOPERATOR1_H
