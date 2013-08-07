#ifndef GOMARKOVCOMMONCAUSE_H
#define GOMARKOVCOMMONCAUSE_H
/**
 * The common cause for GO Markov repairable system.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QVector>
#include "domitem.h"

class GOMarkovOperator;
class Messager;

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
    double breakdownCommon() const;
    void setBreakdownCommon(double value);
    double belta() const;
    void setBelta(double value);
    double gammaC() const;
    void setGammaC(double value);
    QVector<int>* idList() const;
    double calcCommonCause(double time) const;
    bool containOperator(GOMarkovOperator* op) const;
    bool errorDetect(Messager *messager);
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);

protected:
    QVector<GOMarkovOperator*> *_operators;
    QVector<int> *_idList;
    double _breakdownTotal;
    double _breakdownIndividual;
    double _breakdownCommon;
    double _belta;
    double _gammaC;
};

#endif // GOMARKOVCOMMONCAUSE_H
