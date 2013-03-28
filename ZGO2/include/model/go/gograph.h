#ifndef GOGRAPH_H
#define GOGRAPH_H
/**
 * The GO graph.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QVector>

class GOOperator;
class GOSignal;

class GOGraph
{
public:
    GOGraph();
    virtual ~GOGraph();
    QVector<GOOperator*> getSource() const;
    QVector<GOOperator*> getOperator() const;
    QVector<GOSignal*> getSignal() const;
    void addOperator(GOOperator *op);
    void addSignal(GOSignal *signal);

protected:
    QVector<GOOperator*> _source;
    QVector<GOOperator*> _operator;
    QVector<GOSignal*> _signal;
};

#endif // GOGRAPH_H
