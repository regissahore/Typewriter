#ifndef GOPATHSET_H
#define GOPATHSET_H
#include <QVector>
#include <QSet>

class GoOperator;

class GoPathSet
{
public:
    GoPathSet();
    virtual ~GoPathSet();
    int order() const;
    void add(GoOperator *op);
    void removeEnd();
    QVector<GoOperator*>& list();
    void sort();
    QString toIdString();
    QString toCompareString();
    virtual double toProbability() const;
    virtual double toMarkovProbability() const;
    virtual double currentMarkovProbability() const;
    double toImportance() const;
    double toMarkovImportance() const;
    QString toProbabilityString() const;
    QString toMarkovProbabilityString() const;
    QString toImportanceString() const;
    QString toMarkovImportanceString() const;
    virtual GoPathSet* copy();
    bool isContain(GoPathSet *set);
    double totalProbablity() const;
    void setTotalProbablity(const double value);
    QSet<GoOperator*> operatorSet() const;

protected:
    QVector<GoOperator*> _list;
    double _totalProbability;
};

#endif // GOPATHSET_H
