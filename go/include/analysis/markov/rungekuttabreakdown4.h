#ifndef RUNGEKUTTABREAKDOWN4_H
#define RUNGEKUTTABREAKDOWN4_H
#include <QObject>
#include "DoubleVector.h"

class RungeKuttaBreakdown4
{
public:
    RungeKuttaBreakdown4();
    DoubleVector rk0() const;
    DoubleVector rk1() const;
    DoubleVector rk2() const;
    DoubleVector rk3() const;
    DoubleVector rk4() const;
    DoubleVector calcNormalProbability(DoubleVector time, DoubleVector lambda1, DoubleVector lambda2, DoubleVector lambda3, DoubleVector lambda4, DoubleVector mu1, DoubleVector mu2, DoubleVector mu3, DoubleVector mu4);
    DoubleVector func0(DoubleVector t, DoubleVector x0, DoubleVector x1, DoubleVector x2, DoubleVector x3, DoubleVector x4, DoubleVector lambda1, DoubleVector lambda2, DoubleVector lambda3, DoubleVector lambda4, DoubleVector mu1, DoubleVector mu2, DoubleVector mu3, DoubleVector mu4);
    DoubleVector func1(DoubleVector t, DoubleVector x0, DoubleVector x1, DoubleVector x2, DoubleVector x3, DoubleVector x4, DoubleVector lambda1, DoubleVector lambda2, DoubleVector lambda3, DoubleVector lambda4, DoubleVector mu1, DoubleVector mu2, DoubleVector mu3, DoubleVector mu4);
    DoubleVector func2(DoubleVector t, DoubleVector x0, DoubleVector x1, DoubleVector x2, DoubleVector x3, DoubleVector x4, DoubleVector lambda1, DoubleVector lambda2, DoubleVector lambda3, DoubleVector lambda4, DoubleVector mu1, DoubleVector mu2, DoubleVector mu3, DoubleVector mu4);
    DoubleVector func3(DoubleVector t, DoubleVector x0, DoubleVector x1, DoubleVector x2, DoubleVector x3, DoubleVector x4, DoubleVector lambda1, DoubleVector lambda2, DoubleVector lambda3, DoubleVector lambda4, DoubleVector mu1, DoubleVector mu2, DoubleVector mu3, DoubleVector mu4);
    DoubleVector func4(DoubleVector t, DoubleVector x0, DoubleVector x1, DoubleVector x2, DoubleVector x3, DoubleVector x4, DoubleVector lambda1, DoubleVector lambda2, DoubleVector lambda3, DoubleVector lambda4, DoubleVector mu1, DoubleVector mu2, DoubleVector mu3, DoubleVector mu4);

protected:
    DoubleVector _rk0;
    DoubleVector _rk1;
    DoubleVector _rk2;
    DoubleVector _rk3;
    DoubleVector _rk4;
    DoubleVector _rkt;
};

#endif // RUNGEKUTTABREAKDOWN4_H
