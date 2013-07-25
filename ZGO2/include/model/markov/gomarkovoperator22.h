#ifndef GOMARKOVOPERATOR22_H
#define GOMARKOVOPERATOR22_H
/**
 *
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "gomarkovoperator.h"

class GOMarkovOperator22 : public GOMarkovOperator
{
public:
    GOMarkovOperator22();
    ~GOMarkovOperator22();
    QVector<double>* lambda2() const;
    QVector<double>* mu2() const;
    bool errorDetect(Messager *messager);
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);

protected:
    QVector<double> *_lambda2;
    QVector<double> *_mu2;
};

#endif // GOMARKOVOPERATOR1_H
