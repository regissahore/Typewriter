#ifndef GOPATHSETSETSET_H
#define GOPATHSETSETSET_H
#include <QVector>

class GOPathSet;
class GOPathSetSet;
class GOOperator;

class GOPathSetSetSet
{
public:
    struct End
    {
        GOOperator *op;
        int outputIndex;
        int vectorIndex;
        friend bool operator ==(const End &a, const End &b);
        friend bool operator <(const End &a, const End &b);
        friend bool operator >(const End &a, const End &b);
    };

    GOPathSetSetSet();
    virtual ~GOPathSetSetSet();
    void add(GOOperator *endOperator, GOPathSet* path, int outputIndex = 0, int vectorIndex = 0);
    QVector<GOPathSetSet*> list() const;
    QVector<End> endList() const;
    void sort();

protected:
    QVector<GOPathSetSet*> _list;
    QVector<End> _endList;
};

#endif // GOPATHSETSETSET_H
