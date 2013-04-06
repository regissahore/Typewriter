#ifndef GOGRAPH_H
#define GOGRAPH_H
/**
 * The GO graph.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QMap>
#include <QVector>

class GOOperator;
class GOSignal;
class GOPathSet;
class GOCutSet;
class GOPathSetSetSet;

class GOGraph
{
public:
    GOGraph();
    virtual ~GOGraph();
    QVector<int> getSource() const;
    QVector<GOOperator*> getOperator() const;
    QVector<GOSignal*> getSignal() const;
    void addOperator(GOOperator *op);
    void addSignal(GOSignal *signal);
    void calcAccumulativeProbability();
    GOPathSetSetSet findPath(int order);
    GOPathSetSetSet findCut(int order);
    QString getErrorMessage() const;
    bool saveAsHTML(const QString filePath);
    bool saveAsHTML(const QString filePath, GOPathSetSetSet path);

protected:
    struct Output
    {
        GOOperator *op;
        int outputIndex; /** The output index of the operator. */
        int signalIndex;
    };
    QVector<int> _source;
    QVector<GOOperator*> _operator;
    QVector<GOSignal*> _signal;
    QMap<GOOperator*, int> _operatorPos;
    QString _error;
    bool checkCycleAndConnection();
    bool isContainCycleDfs(QVector<bool> &visit, QVector<int> &dfn, QVector<int> &low, QVector<int> &stack, int &timeStamp, int u);
    QVector<GOOperator*> getTopologicalOrder();
    QVector<QVector<Output> > getAncestorList(GOOperator *op, int outputIndex, int signalIndex);
    QVector<Output> getCommonSignalList(GOOperator *op);
    QVector<GOOperator*> getEndList();
    void findPathDfs(GOPathSetSetSet &path, QVector<GOOperator*> &list, GOPathSet &tempPath, int index, int number, int order);
    void findCutDfs(GOPathSetSetSet &cut, QVector<GOOperator*> &list, GOCutSet &tempPath, int index, int number, int order);
};

#endif // GOGRAPH_H
