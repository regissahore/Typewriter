#ifndef GOMARKOVANALYSIS_H
#define GOMARKOVANALYSIS_H
/**
 * The analysis for GO Markov repairable system.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "goanalysis.h"

class GOMarkovOperator;
class GOMarkovOperator9A;
class GOMarkovOperator13;

class GOMarkovAnalysis : public GOAnalysis
{
public:
    GOMarkovAnalysis();
    void calcAccumulativeProbability(GOOperator *op, double time);
    void calcAccumulativeProbability(GOOperator *op, QVector<GOOperator *> commonOperator, QVector<int> commonIndex, double time);

protected:
    void calcAccumulativeProbability_9A1(GOMarkovOperator9A *op, double time);
    void calcAccumulativeProbability_9A2(GOMarkovOperator9A *op, double time);
    void calcAccumulativeProbability_13A(GOMarkovOperator13 *op);
    void calcAccumulativeProbability_13B(GOMarkovOperator13 *op);
    void calcAccumulativeProbability_15A(GOMarkovOperator *op);
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
    void updateOutputMarkov_15_A(GOMarkovOperator *op);
};

#endif // GOMARKOVANALYSIS_H
