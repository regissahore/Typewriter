#ifndef GOMARKOVGRAPH_H
#define GOMARKOVGRAPH_H
/**
 * The GO graph model for GO Markov repairable system.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "gograph.h"

class GOMarkovEquivalent;

class GOMarkovGraph : public GOGraph
{
public:
    GOMarkovGraph();
    ~GOMarkovGraph();
    QVector<GOMarkovEquivalent*> getEquivalent() const;
    void addEquivalent(GOMarkovEquivalent *equivalent);
    bool saveAsHTML(const QString filePath);

protected:
    QVector<GOMarkovEquivalent*> _equivalent;
};

#endif // GOMARKOVGRAPH_H
