#ifndef GOPATHSETSET_H
#define GOPATHSETSET_H
/**
 * The set for GOPathSet.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QVector>

class GOPathSet;

class GOPathSetSet
{
public:
    GOPathSetSet();
    virtual ~GOPathSetSet();
    void add(GOPathSet* path);
    QVector<GOPathSet*> list() const;
    void sort();

protected:
    QVector<GOPathSet*> _list;
};

#endif // GOPATHSETSET_H
