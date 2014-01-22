#ifndef RUNGEKUTTABREAKDOWN3_H
#define RUNGEKUTTABREAKDOWN3_H
#include <QObject>
#include "DoubleVector.h"

class RungeKuttaBreakdown3
{
public:
    RungeKuttaBreakdown3();
    DoubleVector rk0() const;
    DoubleVector rk1() const;
    DoubleVector rk2() const;
    DoubleVector rk3() const;
    DoubleVector calcNormalProbability(DoubleVector time, DoubleVector lambda1, DoubleVector lambda2, DoubleVector lambda3, DoubleVector mu1, DoubleVector mu2, DoubleVector mu3);
    DoubleVector func0(DoubleVector t, DoubleVector x0, DoubleVector x1, DoubleVector x2, DoubleVector x3, DoubleVector lambda1, DoubleVector lambda2, DoubleVector lambda3, DoubleVector mu1, DoubleVector mu2, DoubleVector mu3);
    DoubleVector func1(DoubleVector t, DoubleVector x0, DoubleVector x1, DoubleVector x2, DoubleVector x3, DoubleVector lambda1, DoubleVector lambda2, DoubleVector lambda3, DoubleVector mu1, DoubleVector mu2, DoubleVector mu3);
    DoubleVector func2(DoubleVector t, DoubleVector x0, DoubleVector x1, DoubleVector x2, DoubleVector x3, DoubleVector lambda1, DoubleVector lambda2, DoubleVector lambda3, DoubleVector mu1, DoubleVector mu2, DoubleVector mu3);
    DoubleVector func3(DoubleVector t, DoubleVector x0, DoubleVector x1, DoubleVector x2, DoubleVector x3, DoubleVector lambda1, DoubleVector lambda2, DoubleVector lambda3, DoubleVector mu1, DoubleVector mu2, DoubleVector mu3);

protected:
    DoubleVector _rk0;
    DoubleVector _rk1;
    DoubleVector _rk2;
    DoubleVector _rk3;
    DoubleVector _rkt;
};

#endif // RUNGEKUTTABREAKDOWN3_H
