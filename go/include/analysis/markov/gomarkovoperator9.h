#ifndef GOMARKOVOPERATOR9_H
#define GOMARKOVOPERATOR9_H
#include "GoMarkovOperator.h"

class GoMarkovOperator9 : public GoMarkovOperator
{
public:
    GoMarkovOperator9();
    ~GoMarkovOperator9();
    GoMarkovOperator* copy();
    GoMarkovStatus* markovFeedbackStatus() const;
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);

protected:
    GoMarkovStatus *_feedbackStatus;
};

#endif // GOMARKOVOPERATOR1_H
