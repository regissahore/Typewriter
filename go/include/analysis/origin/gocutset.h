#ifndef GOCUTSET_H
#define GOCUTSET_H
#include "GoPathSet.h"

class GoCutSet : public GoPathSet
{
public:
    GoCutSet();
    GoCutSet *copy();
    double toProbability() const;
    double toMarkovProbability() const;
    QString getProbabilityName() const;
};

#endif // GOCUTSET_H
