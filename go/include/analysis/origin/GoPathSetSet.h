#ifndef GOPATHSETSET_H
#define GOPATHSETSET_H
#include <QVector>

class GoPathSet;

class GoPathSetSet
{
public:
    GoPathSetSet();
    virtual ~GoPathSetSet();
    void add(GoPathSet* path);
    QVector<GoPathSet*> list() const;
    void sort();
    double totalMarkovProbability() const;

protected:
    QVector<GoPathSet*> _list;
};

#endif // GOPATHSETSET_H
