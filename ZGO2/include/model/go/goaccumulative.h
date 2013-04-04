#ifndef GOACCUMULATIVE_H
#define GOACCUMULATIVE_H
/**
 * The accumulative probability.
 * Bind to the outputs of the operator.
 * @author ZHG <CyberZHG@gmail.com>
 */

#include <QVector>

class GOAccumulative
{
public:
    GOAccumulative();
    int number() const;
    void setNumber(int number);
    double accumulative(int index) const;
    void setAccumulative(int index, double value);
    GOAccumulative* copy() const;

protected:
    QVector<long double> _accumulative;
};

#endif // GOACCUMULATIVE_H
