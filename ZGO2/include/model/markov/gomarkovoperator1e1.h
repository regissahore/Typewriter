#ifndef GOMARKOVOPERATOR1E1_H
#define GOMARKOVOPERATOR1E1_H
/**
 * The first extension of GO Markov operator 1.
 * The two fault operator.
 * @author ZHG <CyberZHG@gmail.com>
 */

#include "gomarkovoperator.h"

class GOMarkovStatus;

class GOMarkovOperator1E1 : public GOMarkovOperator
{
public:
    GOMarkovOperator1E1();
    virtual ~GOMarkovOperator1E1();
    GOMarkovStatus* markovStatus2() const;
    void initMarkovStatus(double time);
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);

private:
    GOMarkovStatus *_markovStatus2;
};

#endif // GOMARKOVOPERATOR1E1_H
