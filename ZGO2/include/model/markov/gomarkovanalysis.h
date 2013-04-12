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
    void updateOuputMarkov(GOMarkovOperator *op);
};

#endif // GOMARKOVANALYSIS_H
