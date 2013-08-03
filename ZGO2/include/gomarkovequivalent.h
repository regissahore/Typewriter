#ifndef GOMARKOVEQUIVALENT_H
#define GOMARKOVEQUIVALENT_H
/**
 * The equivalent in the GO Markov Repairable system.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QVector>
#include "identifieditem.h"
#include "domitem.h"

class GOMarkovStatus;
class GOMarkovOperator;

class GOMarkovEquivalent : public IdentifiedItem, public DomItem
{
public:
    GOMarkovEquivalent();
    virtual ~GOMarkovEquivalent();
    QVector<GOMarkovOperator *> *operators() const;
    QVector<GOMarkovEquivalent *> *equivalents() const;
    int I() const;
    int L() const;
    int J() const;
    void setI(int value);
    void setL(int value);
    void setJ(int value);
    virtual GOMarkovStatus getEquivalentStatus() = 0;
    QVector<int>* idList() const;
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);

protected:
    QVector<GOMarkovOperator*> *_operators;
    QVector<GOMarkovEquivalent*> *_equivalents;
    QVector<int> *_idList;
    int _I; /** Shutdown. */
    int _L; /** Repair. */
    int _J; /** Backup. */
};

#endif // GOMARKOVEQUIVALENT_H
