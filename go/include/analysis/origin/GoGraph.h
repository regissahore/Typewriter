#ifndef GOGRAPH_H
#define GOGRAPH_H
#include <QMap>
#include <QVector>
#include "Messager.h"

class GoOperator;
class GoSignal;
class GoPathSet;
class GoCutSet;
class GoPathSetSetSet;
class GoAnalysis;

class GoGraph : public Messager
{
public:
    struct MessageRecord
    {
        QString message;
        int type;
        MessageRecord()
        {
        }
        MessageRecord(const QString &msg, const int type)
        {
            this->message = msg;
            this->type = type;
        }
    };
    GoGraph();
    virtual ~GoGraph();
    QVector<int> getSource() const;
    QVector<GoOperator*> getOperator() const;
    QVector<GoSignal*> getSignal() const;
    void addOperator(GoOperator *op);
    void addSignal(GoSignal *signal);
    virtual void calcAccumulativeProbability();
    virtual GoPathSetSetSet findPath(int order);
    virtual GoPathSetSetSet findCut(int order);
    QString getErrorMessage() const;
    QVector<GoGraph::MessageRecord> messages() const;
    bool saveAsHTML(const QString filePath);
    virtual bool saveAsHTML(const QString filePath, GoPathSetSetSet path);

protected:
    struct Output
    {
        GoOperator *op;
        int outputIndex;
        int signalIndex;
    };
    QVector<MessageRecord> _messages;
    QVector<int> _source;
    QVector<GoOperator*> _operator;
    QVector<GoSignal*> _signal;
    QMap<GoOperator*, int> _operatorPos;
    QString _error;
    GoAnalysis *_analysis;
    bool checkCycleAndConnection();
    virtual bool isContainCycleDfs(QVector<bool> &visit, QVector<int> &dfn, QVector<int> &low, QVector<int> &stack, int &timeStamp, int u);
    virtual QVector<GoOperator*> getTopologicalOrder();
    virtual QVector<QVector<Output> > getAncestorList(GoOperator *op, int outputIndex, int signalIndex);
    QVector<Output> getCommonSignalList(GoOperator *op);
    QVector<GoOperator*> getEndList();
    virtual void findPathDfs(QMap<int, QVector<double>*> &normals, GoPathSetSetSet &path, QVector<GoOperator*> &list, GoPathSet &tempPath, int index, int number, int order);
    virtual void findCutDfs(QMap<int, QVector<double> *> &fails, GoPathSetSetSet &cut, QVector<GoOperator*> &list, GoCutSet &tempPath, int index, int number, int order);
};

#endif // GOGRAPH_H
