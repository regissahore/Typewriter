#ifndef GOPATHSETSETSET_H
#define GOPATHSETSETSET_H
#include <QVector>
#include <QSet>
#include <QMap>

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
    void setIsCut(bool value);
    bool isCut() const;
    void add(GoOperator *endOperator, GoPathSet* path, int outputIndex = 0, int vectorIndex = 0);
    QVector<GoPathSetSet*>& list();
    QVector<End> endList() const;
    void sort();
    double totalMarkovProbability(GoOperator *op, int outputIndex, int vectorIndex) const;
    double totalMarkovProbability(int index) const;
    double totalMarkovProbability(int index, int count);
    void setInterval(double interval);
    double interval() const;
    void setCount(int count);
    int count() const;
    void initCalculation();
    void prepareNextCalculation(int count);
    void finishCalculation();
    void calcWithTime();
    double getProbability(int count, GoPathSet *path);
    double getImportance(int count, GoPathSet *path, GoOperator* end, int outputIndex, int vectorIndex);
    QMap<GoOperator*, QVector<double>>& probabilities();

protected:
    bool _isCut;
    QSet<GoOperator*> _operators;
    QMap<GoOperator*, QVector<double>> _probabilities;
    QVector<GoPathSetSet*> _list;
    QVector<End> _endList;
    double _interval;
    int _count;
};

#endif // GOPATHSETSETSET_H
