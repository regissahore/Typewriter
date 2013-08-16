#ifndef GOPATHSETSETSET_H
#define GOPATHSETSETSET_H
/**
 * 路径的集合的集合，针对产生割集的输出进行排序。
 * @author ZHG <CyberZHG@gmail.com>
 */
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
        int vectorIndex;
        friend bool operator ==(const End &a, const End &b);
        friend bool operator <(const End &a, const End &b);
        friend bool operator >(const End &a, const End &b);
    };

    GOPathSetSetSet();
    virtual ~GOPathSetSetSet();
    void add(GOOperator *endOperator, GOPathSet* path, int vectorIndex = 0);
    QVector<GOPathSetSet*> list() const;
    QVector<End> endList() const;
    void sort();

protected:
    QVector<GOPathSetSet*> _list;
    QVector<End> _endList;
};

#endif // GOPATHSETSETSET_H
