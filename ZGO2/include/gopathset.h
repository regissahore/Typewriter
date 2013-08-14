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
    virtual double toProbability() const;
    virtual double toMarkovProbability() const;
    double toImportance() const;
    double toMarkovImportance() const;
    QString toProbabilityString() const;
    QString toMarkovProbabilityString() const;
    QString toImportanceString() const;
    QString toMarkovImportanceString() const;
    QString toNameString();
    virtual QString getProbabilityName() const;
    virtual GOPathSet* copy();
    bool isContain(GOPathSet *set);
    double totalProbablity() const;
    void setTotalProbablity(const double value);

protected:
    QVector<GOOperator*> _list;
    double _totalProbability;
};

#endif // GOPATHSET_H
