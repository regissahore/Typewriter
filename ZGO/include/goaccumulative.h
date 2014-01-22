#ifndef GOACCUMULATIVE_H
#define GOACCUMULATIVE_H

#include <QVector>

class GOAccumulative
{
public:
    GOAccumulative();
    virtual ~GOAccumulative();
    int number() const;
    void setNumber(int number);
    double accumulative(int index) const;
    double probability(int index) const;
    void setAccumulative(int index, double value);
    GOAccumulative* copy() const;

protected:
    QVector<double> _accumulative;
};

#endif // GOACCUMULATIVE_H
