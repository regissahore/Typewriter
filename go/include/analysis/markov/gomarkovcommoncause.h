#ifndef GOMARKOVCOMMONCAUSE_H
#define GOMARKOVCOMMONCAUSE_H
#include <QVector>
#include "DomItem.h"

class GoMarkovOperator;
class Messager;

class GoMarkovCommonCause : DomItem
{
public:
    GoMarkovCommonCause();
    virtual ~GoMarkovCommonCause();
    QVector<GoMarkovOperator *>* operators() const;
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
    bool containOperator(GoMarkovOperator* op) const;
    bool errorDetect();
    QString error() const;
    GoMarkovCommonCause* copy() const;
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);

protected:
    QVector<GoMarkovOperator*> *_operators;
    QVector<int> *_idList;
    double _breakdownTotal;
    double _breakdownIndividual;
    double _breakdownCommon;
    double _belta;
    double _gammaC;
    QString _error;
};

#endif // GOMARKOVCOMMONCAUSE_H
