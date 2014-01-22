#ifndef GOCUTSET_H
#define GOCUTSET_H
#include "gopathset.h"

class GOCutSet : public GOPathSet
{
public:
    GOCutSet();
    GOCutSet *copy();
    double toProbability() const;
    double toMarkovProbability() const;
    QString getProbabilityName() const;
};

#endif // GOCUTSET_H
