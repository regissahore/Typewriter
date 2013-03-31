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
    QString getErrorMessage() const;

protected:
    QVector<int> _source;
    QVector<GOOperator*> _operator;
    QVector<GOSignal*> _signal;
    QMap<GOOperator*, int> _operatorPos;
    QString _error;

    bool checkCycleAndConnection();
    bool isContainCycleDfs(QVector<int> &colors, int index, int color);
    QVector<GOOperator*> getTopologicalOrder();
};

#endif // GOGRAPH_H
