#ifndef GOMARKOVOPERATOR2_H
#define GOMARKOVOPERATOR2_H
#include "GoMarkovOperator.h"

class GoMarkovOperator2 : public GoMarkovOperator
{
public:
    GoMarkovOperator2();
    ~GoMarkovOperator2();
    int stopWorkNum() const;
    void setStopWorkNum(int value);
    virtual void calcQualitativeProbability();
    void calcOutputMarkovStatus(double time);
    void calcCommonOutputMarkovStatus(QVector<DoubleVector> PR);
    DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index);
    virtual GoMarkovOperator* copy() override;
    virtual void save(QDomDocument &document, QDomElement &root) override;
    virtual bool tryOpen(QDomElement &root) override;

protected:
    int _stopWorkNum;
};

#endif // GOMARKOVOPERATOR1_H
