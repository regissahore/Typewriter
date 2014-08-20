#ifndef GOSIGNAL_H
#define GOSIGNAL_H
#include "IdentifiedItem.h"

class GoOperator;

class GoSignal : public IdentifiedItem
{
public:
    GoSignal();
    virtual ~GoSignal();
    GoOperator* u() const;
    GoOperator* v() const;
    GoOperator* next(GoOperator *op) const;
    void setU(GoOperator* u);
    void setV(GoOperator* v);
    bool isGlobalFeedback() const;
    void setIsGlobalFeedback(const bool value);

protected:
    GoOperator* _u;
    GoOperator* _v;
    bool _isGlobalFeedback;
};

#endif // GOSIGNAL_H
