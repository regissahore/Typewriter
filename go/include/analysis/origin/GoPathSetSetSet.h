#ifndef GOPATHSETSETSET_H
#define GOPATHSETSETSET_H
#include <QVector>
#include <QSet>

class GoPathSet;
class GoPathSetSet;
class GoOperator;
class GoMarkovOperator;

class GoPathSetSetSet
{
public:
    struct End
    {
        GoOperator *op;
        int outputIndex;
        int vectorIndex;
        friend bool operator ==(const End &a, const End &b);
        friend bool operator <(const End &a, const End &b);
        friend bool operator >(const End &a, const End &b);
    };

    GoPathSetSetSet();
    virtual ~GoPathSetSetSet();
    void add(GoOperator *endOperator, GoPathSet* path, int outputIndex = 0, int vectorIndex = 0);
    QVector<GoPathSetSet*> list() const;
    QVector<End> endList() const;
    void sort();
    double totalMarkovProbability(GoOperator *op) const;
    double totalMarkovProbability(int index) const;
    void setInterval(double interval);
    void setCount(int count);
    void initCalculation();
    void prepareNextCalculation(int count);
    void finishCalculation();

protected:
    QSet<GoOperator*> _operators;
    QVector<GoPathSetSet*> _list;
    QVector<End> _endList;
    double _interval;
    int _count;
};

#endif // GOPATHSETSETSET_H
