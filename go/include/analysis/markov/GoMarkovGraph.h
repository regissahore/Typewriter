#ifndef GOMARKOVGRAPH_H
#define GOMARKOVGRAPH_H
#include <QSharedPointer>
#include "GoGraph.h"
#include "DoubleVector.h"

class GoMarkovEquivalent;
class GoMarkovCommonCause;
class GoMarkovChartData;
class GoMarkovOperator;
class GoMarkovStatus;

class GoMarkovGraph : public GoGraph
{
public:
    GoMarkovGraph();
    ~GoMarkovGraph();
    QVector<GoMarkovEquivalent*> getEquivalent() const;
    void addEquivalent(GoMarkovEquivalent *equivalent);
    QVector<GoMarkovCommonCause*> getCommonCause() const;
    void addCommonCause(GoMarkovCommonCause *commonCause);
    void calcAccumulativeProbability(double time);
    QSharedPointer<GoMarkovChartData> calcAccumulativeProbability(double totalTime, int count);
    GoMarkovStatus calcAccumulativeProbability(double time, QString id, double delta, GoMarkovOperator* stopOperator);
    int timeProcess() const;
    int operatorProcess() const;
    int totalOperatorNum() const;
    QString currentOperatorName() const;
    virtual GoPathSetSetSet findPath(int order) override;
    virtual GoPathSetSetSet findCut(int order) override;
    void printQualitativeOutput() const;
    bool saveAsHTML(const QString filePath, GoPathSetSetSet path);

protected:
    int _timeProcess;
    int _operatorProcess;
    QString _currentOperatorName;
    QVector<GoMarkovEquivalent*> _equivalent;
    QVector<GoMarkovCommonCause*> _commonCause;
    virtual bool isContainCycleDfs(QVector<bool> &visit, QVector<int> &dfn, QVector<int> &low, QVector<int> &stack, int &timeStamp, int u) override;
    virtual QVector<QVector<Output> > getAncestorList(GoOperator *op, int outputIndex, int signalIndex) override;
    void findPathDfs(QMap<int, QVector<DoubleVector> *> &normals, GoPathSetSetSet &path, QVector<GoOperator*> &list, GoPathSet &tempPath, int index, int number, int order);
    void findCutDfs(QMap<int, QVector<DoubleVector>* > &fails, GoPathSetSetSet &cut, QVector<GoOperator*> &list, GoCutSet &tempPath, int index, int number, int order);
};

#endif // GOMARKOVGRAPH_H
