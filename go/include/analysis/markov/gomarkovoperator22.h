#ifndef GOMARKOVOPERATOR22_H
#define GOMARKOVOPERATOR22_H
#include "GoMarkovOperator.h"

class GoMarkovOperator22 : public GoMarkovOperator
{
public:
    GoMarkovOperator22();
    ~GoMarkovOperator22();
    QVector<double>* lambda2() const;
    QVector<double>* mu2() const;
    GoMarkovOperator* copy();
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);

protected:
    QVector<double> *_lambda2;
    QVector<double> *_mu2;
};

#endif // GOMARKOVOPERATOR1_H
