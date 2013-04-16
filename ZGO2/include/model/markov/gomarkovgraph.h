#ifndef GOMARKOVGRAPH_H
#define GOMARKOVGRAPH_H
/**
 * The GO graph model for GO Markov repairable system.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "gograph.h"

class GOMarkovEquivalent;
class GOMarkovChartData;

class GOMarkovGraph : public GOGraph
{
public:
    GOMarkovGraph();
    ~GOMarkovGraph();
    QVector<GOMarkovEquivalent*> getEquivalent() const;
    void addEquivalent(GOMarkovEquivalent *equivalent);
    GOMarkovChartData* calcAccumulativeProbability(double totalTime, int count);
    bool saveAsHTML(const QString filePath);

protected:
    QVector<GOMarkovEquivalent*> _equivalent;
};

#endif // GOMARKOVGRAPH_H
