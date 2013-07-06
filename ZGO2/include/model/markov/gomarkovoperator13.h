#ifndef GOMARKOVOPERATOR13_H
#define GOMARKOVOPERATOR13_H
/**
 * The GO Markov operator 13.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QVector>
#include "gomarkovoperator.h"

class GOMarkovOperator13 : public GOMarkovOperator
{
public:
    GOMarkovOperator13();
    virtual ~GOMarkovOperator13();
    void initRelation();
    QVector<QVector<double> >* relation();
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);
    void saveRelation(QDomDocument &document, QDomElement &root);
    bool tryOpenRelation(QDomElement &root);

protected:
    QVector<QVector<double> > *_relation;
};

#endif // GOMARKOVOPERATOR13_H
