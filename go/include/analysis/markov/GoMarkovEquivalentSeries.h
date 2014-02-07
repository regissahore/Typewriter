#ifndef GOMARKOVEQUIVALENTSERIES_H
#define GOMARKOVEQUIVALENTSERIES_H
#include "GoMarkovEquivalent.h"

class GoMarkovStatus;

class GoMarkovEquivalentSeries : public GoMarkovEquivalent
{
public:
    GoMarkovEquivalentSeries();
    GoMarkovStatus getEquivalentStatus();
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);
};

#endif // GOMARKOVEQUIVALENTSERIES_H
