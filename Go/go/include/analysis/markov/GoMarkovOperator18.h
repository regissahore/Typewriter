#ifndef GOMARKOVOPERATOR18_H
#define GOMARKOVOPERATOR18_H
#include "GoMarkovOperator.h"
#include "RungeKuttaMarkov18.h"

class GoMarkovOperator18 : public GoMarkovOperator
{
public:
    GoMarkovOperator18();
    ~GoMarkovOperator18();
    virtual void calcQualitativeProbability() override;
    double lambdaB1() const;
    void setLambdaB1(double value);
    virtual void calcOutputMarkovStatus(double time) override;
    virtual DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index) override;
    virtual GoMarkovOperator* copy() override;
    virtual void save(QDomDocument &document, QDomElement &root) override;
    virtual bool tryOpen(QDomElement &root) override;

protected:
    RungeKuttaMarkov18 _rk18;
    double _lambdaB1;
};

#endif // GOMARKOVOPERATOR1_H
