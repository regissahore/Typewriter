#ifndef GOPATHSETSETSET_H
#define GOPATHSETSETSET_H
/**
 * The set for GOPathSetSet.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QVector>

class GOPathSet;
class GOPathSetSet;
class GOOperator;

class GOPathSetSetSet
{
public:
    GOPathSetSetSet();
    virtual ~GOPathSetSetSet();
    void add(GOOperator *end, GOPathSet* path);
    QVector<GOPathSetSet*> list() const;
    QVector<GOOperator*> endList() const;
    void sort();

protected:
    QVector<GOPathSetSet*> _list;
    QVector<GOOperator*> _endList;
};

#endif // GOPATHSETSETSET_H
