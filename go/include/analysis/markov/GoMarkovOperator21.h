#ifndef GOMARKOVOPERATOR21_H
#define GOMARKOVOPERATOR21_H
#include "GoMarkovOperator.h"

class GoMarkovOperator21 : public GoMarkovOperator
{
public:
    GoMarkovOperator21();
    ~GoMarkovOperator21();
    void calcOutputMarkovStatus(double time);
    virtual void calcQualitativeProbability() override;
    DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index);
    double pathProbability() const;
    double cutProbability() const;
    void setPathProbability(double value);
    void setCutProbability(double value);

protected:
    double _pathProbability;
    double _cutProbability;
};

#endif // GOMARKOVOPERATOR1_H
