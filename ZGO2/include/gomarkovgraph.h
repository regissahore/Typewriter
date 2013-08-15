#ifndef GOMARKOVGRAPH_H
#define GOMARKOVGRAPH_H
/**
 * The GO graph model for GO Markov repairable system.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "gograph.h"
#include "doublevector.h"

class GOMarkovEquivalent;
class GOMarkovCommonCause;
class GOMarkovChartData;
class GOMarkovOperator;
class GOMarkovStatus;

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
    GOMarkovStatus calcAccumulativeProbability(double time, QString id, double delta, GOMarkovOperator* stopOperator);
    bool saveAsHTML(const QString filePath);
    bool saveAsHTML(const QString filePath, GOPathSetSetSet path);

protected:
    QVector<GOMarkovEquivalent*> _equivalent;
    QVector<GOMarkovCommonCause*> _commonCause;
    virtual bool isContainCycleDfs(QVector<bool> &visit, QVector<int> &dfn, QVector<int> &low, QVector<int> &stack, int &timeStamp, int u);
    virtual QVector<GOOperator*> getTopologicalOrder();
    virtual QVector<QVector<Output> > getAncestorList(GOOperator *op, int outputIndex, int signalIndex);
    virtual GOPathSetSetSet findPath(int order);
    virtual GOPathSetSetSet findCut(int order);
    virtual void findPathDfs(QMap<int, QVector<DoubleVector> *> &normals, GOPathSetSetSet &path, QVector<GOOperator*> &list, GOPathSet &tempPath, int index, int number, int order);
    virtual void findCutDfs(QMap<int, QVector<DoubleVector>* > &fails, GOPathSetSetSet &cut, QVector<GOOperator*> &list, GOCutSet &tempPath, int index, int number, int order);
};

#endif // GOMARKOVGRAPH_H
