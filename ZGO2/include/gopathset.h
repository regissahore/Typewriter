#ifndef GOPATHSET_H
#define GOPATHSET_H
/**
 * The structure used to record path.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QVector>

class GOOperator;

class GOPathSet
{
public:
    GOPathSet();
    virtual ~GOPathSet();
    int order() const;
    void add(GOOperator *op);
    void removeEnd();
    QVector<GOOperator*> list() const;
    void sort();
    QString toIdString();
    QString toCompareString();
    virtual QString toProbabilityString();
    virtual QString toMarkovProbabilityString();
    virtual GOPathSet* copy();
    bool isContain(GOPathSet *set);

protected:
    QVector<GOOperator*> _list;
};

#endif // GOPATHSET_H
