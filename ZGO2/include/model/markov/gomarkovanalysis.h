#ifndef GOMARKOVANALYSIS_H
#define GOMARKOVANALYSIS_H
/**
 * The analysis for GO Markov repairable system.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "goanalysis.h"

class GOMarkovOperator;

class GOMarkovAnalysis : public GOAnalysis
{
public:
    GOMarkovAnalysis();
    virtual void calcAccumulativeProbability(GOOperator *op);
    virtual void calcAccumulativeProbability(GOOperator *op, QVector<GOOperator *> commonOperator, QVector<int> commonIndex);

protected:
    void updateOutputMarkov(GOMarkovOperator *op);
    void updateOutputMarkov_1(GOMarkovOperator *op);
    void updateOutputMarkov_2(GOMarkovOperator *op);
    void updateOutputMarkov_5(GOMarkovOperator *op);
    void updateOutputMarkov_6(GOMarkovOperator *op);
    void updateOutputMarkov_10(GOMarkovOperator *op);
    void updateOutputMarkov_11(GOMarkovOperator *op);
    void updateOutputMarkov_1_E1(GOMarkovOperator *op);
    void updateOutputMarkov_9_A1(GOMarkovOperator *op);
    void updateOutputMarkov_9_A2(GOMarkovOperator *op);
    void updateOutputMarkov_13_A(GOMarkovOperator *op);
    void updateOutputMarkov_13_B(GOMarkovOperator *op);
    void updateOutputMarkov_15_A(GOMarkovOperator *op);
};

#endif // GOMARKOVANALYSIS_H
