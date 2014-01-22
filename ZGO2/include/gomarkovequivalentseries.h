#ifndef GOMARKOVEQUIVALENTSERIES_H
#define GOMARKOVEQUIVALENTSERIES_H
#include "gomarkovequivalent.h"

class GOMarkovStatus;

class GOMarkovEquivalentSeries : public GOMarkovEquivalent
{
public:
    GOMarkovEquivalentSeries();
    GOMarkovStatus getEquivalentStatus();
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);
};

#endif // GOMARKOVEQUIVALENTSERIES_H
