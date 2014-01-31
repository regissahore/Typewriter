#ifndef GOMARKOVOPERATOR18A_H
#define GOMARKOVOPERATOR18A_H
#include "GoMarkovOperator.h"

class GoMarkovOperator18A : public GoMarkovOperator
{
public:
    GoMarkovOperator18A();
    ~GoMarkovOperator18A();
    virtual void calcQualitativeProbability();
    double backup() const;
    void setBackup(double value);
    void calcOutputMarkovStatus(double time);
    void calcCommonOutputMarkovStatus(QVector<DoubleVector> PR);
    DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index);
    GoMarkovOperator* copy();
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);

protected:
    double _backup;
};

#endif // GOMARKOVOPERATOR18_H
