#ifndef GOMARKOVOPERATOR9A_H
#define GOMARKOVOPERATOR9A_H
/**
 * The Markov operator 9 with feedback.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "gomarkovoperator.h"

class GOMarkovStatus;

class GOMarkovOperator9A : public GOMarkovOperator
{
public:
    GOMarkovOperator9A();
    virtual ~GOMarkovOperator9A();
    GOMarkovStatus* markovFeedbackStatus() const;
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);

private:
    GOMarkovStatus *_feedbackStatus;
};

#endif // GOMARKOVOPERATOR9A_H
