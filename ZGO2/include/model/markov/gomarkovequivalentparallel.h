#ifndef GOMARKOVEQUIVALENTPARALLEL_H
#define GOMARKOVEQUIVALENTPARALLEL_H
/**
 * The parallel equivalent.
 * @author ZHG <CyberZHG@gmail.com>
 */

#include "gomarkovequivalent.h"

class GOMarkovStatus;

class GOMarkovEquivalentParallel : public GOMarkovEquivalent
{
public:
    GOMarkovEquivalentParallel();
    GOMarkovStatus getEquivalentStatus();
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);
};

#endif // GOMARKOVEQUIVALENTPARALLEL_H
