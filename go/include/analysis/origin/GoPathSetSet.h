#ifndef GOPATHSETSET_H
#define GOPATHSETSET_H
#include <QVector>
#include <QSet>

class GoOperator;
class GoPathSet;

class GoPathSetSet
{
public:
    GoPathSetSet();
    virtual ~GoPathSetSet();
    void add(GoPathSet* path);
    QVector<GoPathSet*>& list();
    void sort();
    double totalMarkovProbability() const;
    QSet<GoOperator*> operatorSet() const;

protected:
    QVector<GoPathSet*> _list;
};

#endif // GOPATHSETSET_H
