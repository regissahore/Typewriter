#ifndef GOMARKOVOPERATOR18A_H
#define GOMARKOVOPERATOR18A_H
#include "GoMarkovOperator.h"

class GoMarkovOperator18A : public GoMarkovOperator
{
public:
    GoMarkovOperator18A();
    ~GoMarkovOperator18A();
    virtual void calcQualitativeProbability() override final;
    double backup() const;
    void setBackup(double value);
    virtual void calcOutputMarkovStatus(double time) override final;
    virtual void calcCommonOutputMarkovStatus(QVector<DoubleVector> PR) override final;
    virtual DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index) override final;
    virtual GoMarkovOperator* copy() override final;
    virtual void save(QDomDocument &document, QDomElement &root) override final;
    virtual bool tryOpen(QDomElement &root) override final;

protected:
    double _backup;
};

#endif // GOMARKOVOPERATOR18_H
