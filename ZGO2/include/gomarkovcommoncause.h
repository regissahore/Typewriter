#ifndef GOMARKOVCOMMONCAUSE_H
#define GOMARKOVCOMMONCAUSE_H
/**
 * The common cause for GO Markov repairable system.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QVector>
#include "domitem.h"

class GOMarkovOperator;

class GOMarkovCommonCause : DomItem
{
public:
    GOMarkovCommonCause();
    virtual ~GOMarkovCommonCause();
    QVector<GOMarkovOperator *>* operators() const;
    double breakdownTotal() const;
    void setBreakdownTotal(double value);
    double breakdownIndividual() const;
    void setBreakdownIndividual(double value);
    double gammaC() const;
    void setGammaC(double value);
    double breakdownCommon() const;
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);
    QVector<int>* idList() const;
    double calcCommonCause(double time) const;
    bool containOperator(GOMarkovOperator* op) const;

protected:
    QVector<GOMarkovOperator*> *_operators;
    QVector<int> *_idList;
    double _breakdownTotal;
    double _breakdownIndividual;
    double _gammaC;
};

#endif // GOMARKOVCOMMONCAUSE_H
