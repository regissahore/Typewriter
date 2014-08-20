#ifndef GOMARKOVEQUIVALENTPARALLEL_H
#define GOMARKOVEQUIVALENTPARALLEL_H

#include "GoMarkovEquivalent.h"

class GoMarkovStatus;

class GoMarkovEquivalentParallel : public GoMarkovEquivalent
{
public:
    GoMarkovEquivalentParallel();
    GoMarkovStatus getEquivalentStatus();
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);
};

#endif // GOMARKOVEQUIVALENTPARALLEL_H
