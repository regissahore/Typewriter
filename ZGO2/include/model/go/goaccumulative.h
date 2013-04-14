#ifndef GOACCUMULATIVE_H
#define GOACCUMULATIVE_H
/**
 * The accumulative probability.
 * Bind to the outputs of the operator.
 * @author ZHG <CyberZHG@gmail.com>
 */

#include <QVector>
#include "bigdecimal.h"

class GOAccumulative
{
public:
    GOAccumulative();
    virtual ~GOAccumulative();
    int number() const;
    void setNumber(int number);
    BigDecimal accumulative(int index) const;
    BigDecimal probability(int index) const;
    void setAccumulative(int index, BigDecimal value);
    GOAccumulative* copy() const;

protected:
    QVector<BigDecimal> _accumulative;
};

#endif // GOACCUMULATIVE_H
