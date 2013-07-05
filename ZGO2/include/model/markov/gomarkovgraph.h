#ifndef GOMARKOVGRAPH_H
#define GOMARKOVGRAPH_H
/**
 * The GO graph model for GO Markov repairable system.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "gograph.h"

class GOMarkovEquivalent;
class GOMarkovCommonCause;
class GOMarkovChartData;
class GOMarkovOperator;

class GOMarkovGraph : public GOGraph
{
public:
    GOMarkovGraph();
    ~GOMarkovGraph();
    QVector<GOMarkovEquivalent*> getEquivalent() const;
    void addEquivalent(GOMarkovEquivalent *equivalent);
    QVector<GOMarkovCommonCause*> getCommonCause() const;
    void addCommonCause(GOMarkovCommonCause *commonCause);
    void calcAccumulativeProbability(double time);
    GOMarkovChartData* calcAccumulativeProbability(double totalTime, int count);
    bool saveAsHTML(const QString filePath);

protected:
    QVector<GOMarkovEquivalent*> _equivalent;
    QVector<GOMarkovCommonCause*> _commonCause;
};

#endif // GOMARKOVGRAPH_H
