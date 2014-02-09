#ifndef GOPATHSETSETSET_H
#define GOPATHSETSETSET_H
#include <QVector>

class GoPathSet;
class GoPathSetSet;
class GoOperator;

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

protected:
    QVector<GoPathSetSet*> _list;
    QVector<End> _endList;
};

#endif // GOPATHSETSETSET_H
