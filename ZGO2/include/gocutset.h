#ifndef GOCUTSET_H
#define GOCUTSET_H
/**
 * The structure used to record cut.
 * @author ZHG <CyberZHG@gmail.com>
 */
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
