#ifndef GOMARKOVANALYSIS_H
#define GOMARKOVANALYSIS_H
#include "GoAnalysis.h"
#include "DoubleVector.h"

class GoMarkovOperator;
class GoMarkovOperator9A;
class GoMarkovOperator13;

class GoMarkovAnalysis : public GoAnalysis
{
public:
    GoMarkovAnalysis();
    void calcMarkovStatus(GoMarkovOperator *op, QVector<GoOperator *> commonOperator, QVector<int> commonIndex, double time);
    DoubleVector calcTempMarkovStatus(GoMarkovOperator *op, int index, QVector<GoOperator *> &commonOperator, QVector<int> &commonIndex, QVector<DoubleVector> &normalValues, double time);

protected:
    void calcAccumulativeProbability_9A1(GoMarkovOperator9A *op, double time);
    void calcAccumulativeProbability_9A2(GoMarkovOperator9A *op, double time);
    void calcAccumulativeProbability_13A(GoMarkovOperator13 *op);
    void calcAccumulativeProbability_13B(GoMarkovOperator13 *op);
    void calcAccumulativeProbability_15A(GoMarkovOperator *op);
    void updateOutputMarkov(GoMarkovOperator *op);
    void updateOutputMarkov_1(GoMarkovOperator *op);
    void updateOutputMarkov_2(GoMarkovOperator *op);
    void updateOutputMarkov_5(GoMarkovOperator *op);
    void updateOutputMarkov_6(GoMarkovOperator *op);
    void updateOutputMarkov_10(GoMarkovOperator *op);
    void updateOutputMarkov_11(GoMarkovOperator *op);
    void updateOutputMarkov_1_E1(GoMarkovOperator *op);
    void updateOutputMarkov_9_A1(GoMarkovOperator *op);
    void updateOutputMarkov_9_A2(GoMarkovOperator *op);
    void updateOutputMarkov_15_A(GoMarkovOperator *op);
};

#endif // GOMARKOVANALYSIS_H
