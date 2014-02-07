#ifndef GOMARKOVEQUIVALENT_H
#define GOMARKOVEQUIVALENT_H
#include <QVector>
#include "IdentifiedItem.h"
#include "DomItem.h"

class GoMarkovStatus;
class GoMarkovOperator;

class GoMarkovEquivalent : public IdentifiedItem, public DomItem
{
public:
    GoMarkovEquivalent();
    virtual ~GoMarkovEquivalent();
    QVector<GoMarkovOperator *> *operators() const;
    QVector<GoMarkovEquivalent *> *equivalents() const;
    int I() const;
    int L() const;
    int J() const;
    void setI(int value);
    void setL(int value);
    void setJ(int value);
    virtual GoMarkovStatus getEquivalentStatus() = 0;
    QVector<int>* idList() const;
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);

protected:
    QVector<GoMarkovOperator*> *_operators;
    QVector<GoMarkovEquivalent*> *_equivalents;
    QVector<int> *_idList;
    int _I; 
    int _L; 
    int _J; 
};

#endif // GOMARKOVEQUIVALENT_H
