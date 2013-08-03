#ifndef GOSIGNAL_H
#define GOSIGNAL_H
/**
 * The GO signal。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "identifieditem.h"

class GOOperator;

class GOSignal : public IdentifiedItem
{
public:
    GOSignal();
    virtual ~GOSignal();
    GOOperator* u() const;
    GOOperator* v() const;
    GOOperator* next(GOOperator *op) const;
    void setU(GOOperator* u);
    void setV(GOOperator* v);

protected:
    GOOperator* _u; /** One ID of the connected operator. */
    GOOperator* _v; /** The other ID of the connected operator. */
};

#endif // GOSIGNAL_H
