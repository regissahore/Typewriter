#ifndef GOCUTSET_H
#define GOCUTSET_H
#include "GoPathSet.h"

class GoCutSet : public GoPathSet
{
public:
    GoCutSet();
    GoCutSet *copy() override;
    double toProbability() const override;
    double toMarkovProbability() const override;
};

#endif // GOCUTSET_H
