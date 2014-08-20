#ifndef GOACCUMULATIVE_H
#define GOACCUMULATIVE_H

#include "stable.h"

class GoAccumulative
{
public:
    GoAccumulative();
    virtual ~GoAccumulative();
    int number() const;
    void setNumber(int number);
    double accumulative(int index) const;
    double probability(int index) const;
    void setAccumulative(int index, double value);
    GoAccumulative* copy() const;

protected:
    QVector<double> _accumulative;
};

#endif // GOACCUMULATIVE_H
