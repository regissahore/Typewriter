#ifndef GOPATHSETSET_H
#define GOPATHSETSET_H
/**
 * 路径的集合，针对路径的阶数和操作符的ID进行排序。
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
