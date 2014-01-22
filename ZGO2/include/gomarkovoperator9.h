#ifndef GOMARKOVOPERATOR9_H
#define GOMARKOVOPERATOR9_H
#include "gomarkovoperator.h"

class GOMarkovOperator9 : public GOMarkovOperator
{
public:
    GOMarkovOperator9();
    ~GOMarkovOperator9();
    GOMarkovOperator* copy();
    GOMarkovStatus* markovFeedbackStatus() const;
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);

protected:
    GOMarkovStatus *_feedbackStatus;
};

#endif // GOMARKOVOPERATOR1_H
