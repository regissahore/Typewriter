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
    GOPathSet *copy();
    QString toProbabilityString();
    QString toMarkovProbabilityString();
};

#endif // GOCUTSET_H
