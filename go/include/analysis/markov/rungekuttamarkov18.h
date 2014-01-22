#ifndef RUNGEKUTTAMARKOV18_H
#define RUNGEKUTTAMARKOV18_H
#include <QObject>
#include "DoubleVector.h"

class RungeKuttaMarkov18
{
public:
    RungeKuttaMarkov18();
    DoubleVector rk0() const;
    DoubleVector rk1() const;
    DoubleVector rk2() const;
    DoubleVector rk3() const;
    DoubleVector lambdaB1() const;
    void setLambdaB1(const DoubleVector value);
    DoubleVector calcNormalProbability(DoubleVector time, DoubleVector lambda1, DoubleVector lambda2, DoubleVector mu1, DoubleVector mu2);
    DoubleVector func0(DoubleVector t, DoubleVector x0, DoubleVector x1, DoubleVector x2, DoubleVector x3, DoubleVector lambda1, DoubleVector lambda2, DoubleVector mu1, DoubleVector mu2);
    DoubleVector func1(DoubleVector t, DoubleVector x0, DoubleVector x1, DoubleVector x2, DoubleVector x3, DoubleVector lambda1, DoubleVector lambda2, DoubleVector mu1, DoubleVector mu2);
    DoubleVector func2(DoubleVector t, DoubleVector x0, DoubleVector x1, DoubleVector x2, DoubleVector x3, DoubleVector lambda1, DoubleVector lambda2, DoubleVector mu1, DoubleVector mu2);
    DoubleVector func3(DoubleVector t, DoubleVector x0, DoubleVector x1, DoubleVector x2, DoubleVector x3, DoubleVector lambda1, DoubleVector lambda2, DoubleVector mu1, DoubleVector mu2);

protected:
    DoubleVector _rk0;
    DoubleVector _rk1;
    DoubleVector _rk2;
    DoubleVector _rk3;
    DoubleVector _rkt;
    DoubleVector _lambdaB1;
};

#endif // RUNGEKUTTAMARKOV18_H
